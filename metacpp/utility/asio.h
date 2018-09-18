//
// Created by shniu on 18-9-18.
//

#ifndef METACHAIN_ASIO_H
#define METACHAIN_ASIO_H

#include <boost/asio.hpp>
#include <boost/thread.hpp>

namespace metachain {
namespace asio {

    // aliases
    typedef boost::asio::io_service io_service;
    typedef boost::asio::ip::address address;
    typedef boost::asio::ip::address_v4 ipv4_address;
    typedef boost::asio::ip::address_v6 ipv6_address;
    typedef boost::asio::ip::tcp tcp;
    typedef boost::asio::ip::tcp::endpoint endpoint;

    typedef tcp::socket socket;
    typedef tcp::acceptor acceptor;
    typedef tcp::resolver resolver;
    typedef tcp::resolver::query query;

    typedef boost::thread thread;

    typedef std::shared_ptr<socket> socket_ptr;

    constexpr int max_connections = boost::asio::socket_base::max_connections;

}  // asio
}  // metachain

#endif //METACHAIN_ASIO_H
