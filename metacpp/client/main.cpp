//
// Created by shniu on 18-9-1.
//

#include <iostream>
#include <boost/asio.hpp>
#include <boost/array.hpp>

using namespace std;

using boost::asio::io_service;
using boost::asio::ip::tcp;
using boost::asio::ip::address;

void connect_handler(const boost::system::error_code &ec);

// asio_usage
void asio_usage() {
    io_service service;
    tcp::endpoint endpoint(address::from_string("127.0.0.1"), 4000);
    tcp::socket socket(service);
    socket.async_connect(endpoint, connect_handler);
    service.run();
}

// sync asio client to get daytime from the server
void asio_sync_cli(int argc, char** argv) {

    try {
        io_service io;

        /*tcp::resolver resolver(io);
        tcp::resolver::query query(argv[1], "daytime");
        tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);*/
        tcp::endpoint endpoint(address::from_string("127.0.0.1"), 4001);

        tcp::socket sock(io);
        sock.connect(endpoint);
        // boost::asio::connect(sock, endpoint);

        for (;;) {
            boost::array<char, 128> buf;
            boost::system::error_code error;

            size_t len = sock.read_some(boost::asio::buffer(buf), error);
            if (error == boost::asio::error::eof) {
                break;
            } else if (error) {
                throw boost::system::system_error(error);
            }

            cout.write(buf.data(), len);
        }
    } catch (exception &e) {
        cout << e.what() << endl;
    }

}

int main(int argc, char** argv) {
    // asio_usage();
    asio_sync_cli(argc, argv);
    return 0;
}

void connect_handler(const boost::system::error_code &ec) {
    cout << "connect succeed. \n"
         << ec.message()
         << endl;
}
