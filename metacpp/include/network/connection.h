//
// Created by shniu on 18-8-31.
//

#ifndef METACHAIN_CONNECTION_H
#define METACHAIN_CONNECTION_H

#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>

namespace metachain {

    using boost::asio::ip::tcp;
    using boost::asio::io_service;

    // This class represents a connection to one other peer.
    class Connection : public boost::enable_shared_from_this<Connection> {
    public:
        Connection(io_service &io);
        ~Connection();

    private:
        tcp::socket _socket;
};

}  // metachain

#endif //METACHAIN_CONNECTION_H
