//
// Created by shniu on 18-9-1.
//

#include <iostream>
#include <boost/asio.hpp>

using namespace std;

using boost::system::error_code;
using boost::asio::io_service;
using boost::asio::ip::tcp;
using boost::asio::ip::address;

void connect_handler(const error_code &ec);

int main(int argc, char** argv) {
    io_service service;
    tcp::endpoint endpoint(address::from_string("127.0.0.1"), 4000);
    tcp::socket socket(service);
    socket.async_connect(endpoint, connect_handler);

    return 0;
}

void connect_handler(const error_code &ec) {
    cout << "connect succeed. \n"
         << ec.message()
         << endl;
}
