//
// Created by shniu on 18-8-31.
//

#ifndef METACHAIN_CONNECTION_H
#define METACHAIN_CONNECTION_H

#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

namespace metachain {
namespace network {

    using boost::asio::ip::tcp;
    using boost::asio::io_service;

    // This class represents a connection to one other peer.
    class Connection :
            public boost::enable_shared_from_this<Connection> {
    public:
        typedef boost::shared_ptr<Connection> connection_ptr;

        Connection(io_service &ios);

        ~Connection();

    private:
        tcp::socket m_socket;
    };

}  // network
}  // metachain

#endif //METACHAIN_CONNECTION_H
