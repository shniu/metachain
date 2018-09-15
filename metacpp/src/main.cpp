//
// Created by shniu on 18-7-12.
//

#include <iostream>
#include <vector>
#include <functional>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/enable_shared_from_this.hpp>

using namespace std;

using boost::asio::ip::tcp;
using boost::asio::io_service;
typedef boost::shared_ptr<tcp::socket> socket_ptr;

/*class peer {
public:
    void connect();
    void listen();
    void open();
    void broadcast();  // message for now
    void send(); // send message
};*/
// p2p network
// build a server using `boost::asio` and `boost::thread`
// every node have some action:
//    - connect
//    - listen
//    - open
//    - broadcast
//    - etc.

void client_session(socket_ptr sock) {
    cout << "Accept a request" << endl;
}

void asio_usage1() {
    io_service service;
    // support ipv4 for now, and listen on 4000
    tcp::endpoint endpoint(tcp::v4(), 4000);
    tcp::acceptor acceptor(service, endpoint);

    // Way 1: use while loop
    while (true) {
        socket_ptr sock(new tcp::socket(service));
        acceptor.accept(*sock);
        boost::thread(boost::bind(client_session, sock));
    }

    // Way 2: use async_accept
    /*void handle_accept(socket_ptr sock, const boost::system::error_code &ec);
    void start_accept(socket_ptr sock);

    socket_ptr sock(new tcp::socket(service));
    start_accept(sock);
    service.run();

    void handle_accept(socket_ptr sock, const boost::system::error_code &ec) {
        if (ec)
            return;

        //socket_ptr sock(new tcp::socket(service));
        start_accept(sock);
    }
    void start_accept(socket_ptr sock) {
        acceptor.async_accept(*sock, boost::bind(handle_accept, sock, _1));
    }*/
}

// using a timer sync
void asio_timer_sync() {
    io_service io;

    boost::asio::deadline_timer t(io, boost::posix_time::seconds(5));
    t.wait();

    cout << "Hello boost asio!" << endl;
}

// using a timer async, means having a callback function
void print(const boost::system::error_code &ec) {
    cout << "Hello boost asio async" << endl;
}
void asio_timer_async() {
    io_service io;

    boost::asio::deadline_timer t(io, boost::posix_time::seconds(5));
    t.async_wait(&print);

    io.run();
}

// binding arguments to a handler
void print_binding_param(const boost::system::error_code &ec, boost::asio::deadline_timer *t, int* count) {
    if (*count < 5) {
        cout << *count << endl;
        ++(*count);
        t->expires_at(t->expires_at() + boost::posix_time::seconds(1));
        t->async_wait(boost::bind(print_binding_param, boost::asio::placeholders::error, t, count));
    }
}
void asio_binding_param() {
    io_service io;

    int count = 0;
    boost::asio::deadline_timer t(io, boost::posix_time::seconds(1));
    t.async_wait(boost::bind(print_binding_param, boost::asio::placeholders::error, &t, &count));
    io.run();
    cout << "Final count is: "
         << count
         << endl;
}

// using a member function
class printer {
public:
    printer(io_service &io) : _timer(io, boost::posix_time::seconds(1)), _count(0) {
        _timer.async_wait(boost::bind(&printer::print, this));
    }

    ~printer() {
        cout << "Final count is: "
             << _count
             << endl;
    }

    void print() {
        if (_count < 5) {
            cout << _count << endl;
            ++_count;
            _timer.expires_at(_timer.expires_at() + boost::posix_time::seconds(1));
            _timer.async_wait(boost::bind(&printer::print, this));
        }
    }

private:
    boost::asio::deadline_timer _timer;
    int _count;
};
void asio_class_member() {
    io_service io;
    printer p(io);
    io.run();
}

// sync multithread
class multithread_printer {

public:
    multithread_printer(io_service &io) :
            _strand(io),
            _timer1(io, boost::posix_time::seconds(1)),
            _timer2(io, boost::posix_time::seconds(1)),
            _count(0) {
        _timer1.async_wait(_strand.wrap(boost::bind(&multithread_printer::print1, this)));
        _timer2.async_wait(_strand.wrap(boost::bind(&multithread_printer::print2, this)));
    }

    ~multithread_printer() {
        cout << "Final count is: "
             << _count
             << endl;
    }

    void print1() {
        if (_count < 10) {
            cout << "Timer1 "
                 << _count << endl;
            ++_count;
            _timer1.expires_at(_timer1.expires_at() + boost::posix_time::seconds(1));
            _timer1.async_wait(boost::bind(&multithread_printer::print1, this));
        }
    }

    void print2() {
        if (_count < 10) {
            cout << "Timer2 "
                 << _count << endl;
            ++_count;
            _timer2.expires_at(_timer2.expires_at() + boost::posix_time::seconds(1));
            _timer2.async_wait(boost::bind(&multithread_printer::print2, this));
        }
    }

private:
    boost::asio::io_service::strand _strand;
    boost::asio::deadline_timer _timer1;
    boost::asio::deadline_timer _timer2;
    int _count;
};
void asio_multithread() {
    io_service io;
    multithread_printer mp(io);
    boost::thread t(boost::bind(&boost::asio::io_service::run, &io));
    io.run();
    t.join();
}

// asio sync daytime server
string make_daytime_string() {
    time_t now = time(nullptr);
    return ctime(&now);
}
void asio_sync_daytime_server() {

    try {
        io_service io;

        tcp::acceptor acceptor(io, tcp::endpoint(tcp::v4(), 4001));

        for (;;) {
            tcp::socket sock(io);
            acceptor.accept(sock);

            string message = make_daytime_string();

            boost::system::error_code ignored_error;
            cout << "echo back " << message << endl;
            boost::asio::write(sock, boost::asio::buffer(message), ignored_error);
        }
    } catch (exception &e) {
        cerr << e.what() << endl;
    }

}

// asio async daytime server
class tcp_connection : public boost::enable_shared_from_this<tcp_connection> {
public:
    typedef boost::shared_ptr<tcp_connection> pointer;
    static pointer create(io_service &io) {
        return pointer(new tcp_connection(io));
    }

    tcp::socket& socket() {
        return _socket;
    }

    void start() {
        _message = make_daytime_string();
        boost::asio::async_write(_socket, boost::asio::buffer(_message),
                                 boost::bind(&tcp_connection::handle_write, shared_from_this(),
                                 boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred()));
    }

private:
    tcp_connection(io_service &io) : _socket(io) {}

    void handle_write(const boost::system::error_code& ec, size_t bytes_transfered) {

    }

    tcp::socket _socket;
    string _message;

};
class tcp_server {

public:
    tcp_server(io_service &io) : _acceptor(io, tcp::endpoint(tcp::v4(), 4001)) {
        start_accept();
    }

private:
    void start_accept() {
        tcp_connection::pointer new_connection = tcp_connection::create(_acceptor.get_io_service());
        _acceptor.async_accept(new_connection->socket(),
                               boost::bind(&tcp_server::handle_accept, this, new_connection, boost::asio::placeholders::error));
    }

    void handle_accept(tcp_connection::pointer new_connection, const boost::system::error_code& ec) {
        if (!ec) {
            new_connection->start();
        }
        start_accept();
    }

    tcp::acceptor _acceptor;

};
void asio_async_server() {
    try {
        io_service io;
        tcp_server server(io);
        io.run();

    } catch (exception &e) {
        cerr << e.what() << endl;
    }
}

// std function
int test_std_function(int a) {
    return a;
}
auto test_func_lambda = [](int a) -> int { return a; };
class test_func_cls {
public:
    int operator()(int a) {
        return a;
    }
};
class test_cls_2 {
public:
    int test(int a){
        return a;
    };
    static int static_test(int a) {
        return a;
    }
};
void std_function() {
    std::function<int(int)> std_func;
    std_func = test_func_lambda;
    auto a = std_func(2);
    std::cout << a << std::endl;

    test_func_cls tfcls;
    std_func = tfcls;
    a = std_func(5);
    std::cout << a << std::endl;

    test_cls_2 tc2;
    std_func = std::bind(&test_cls_2::test, tc2, std::placeholders::_1);
    a = std_func(10);
    std::cout << a << std::endl;

    std_func = test_cls_2::static_test;
    a = std_func(100);
    std::cout << a << std::endl;
}

// main
int main(int argc, char** argv) {
    // asio_usage1();
    // asio_timer_sync();
    // asio_timer_async();
    // asio_binding_param();
    // asio_class_member();
    // asio_multithread();
    // asio_sync_daytime_server();
    // asio_async_server();
    std_function();
}

/*

  Ref:
    - https://mmoaay.gitbooks.io/boost-asio-cpp-network-programming-chinese
    - boost asio website
    - https://github.com/Organic-Code/Breep
    - https://github.com/kgryte/awesome-peer-to-peer
*/
