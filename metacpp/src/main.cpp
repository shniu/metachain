//
// Created by shniu on 18-7-12.
//

#include <iostream>
#include <vector>
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>

using namespace std;

using boost::asio::ip::tcp;
using boost::asio::io_service;
typedef boost::shared_ptr<tcp::socket> socket_ptr;

class peer {
public:
    void connect();
    void listen();
    void open();
    void broadcast();  // message for now
    void send(); // send message
};

void client_session(socket_ptr sock);

// main
int main(int argc, char** argv) {

    // p2p network
    // build a server using `boost::asio` and `boost::thread`
    // every node have some action:
    //    - connect
    //    - listen
    //    - open
    //    - broadcast
    //    - etc.

    io_service service;
    // support ipv4 for now, and listen on 4000
    tcp::endpoint endpoint(tcp::v4(), 4000);
    tcp::acceptor acceptor(service, endpoint);

    while (true) {
        socket_ptr sock(new tcp::socket(service));
        acceptor.accept();
        boost::thread(boost::bind(client_session, sock));
    }
}

void client_session(socket_ptr sock) {
    cout << "Accept a request" << endl;
}

/*

  1. 完成搭建一个p2p网络，实例节点间可以发送 hello message
  2. 扩展节点功能，改造 message 为 Block 结构
  3. 节点可接受交易请求，并打包到 Block 中，广播出去
*/
