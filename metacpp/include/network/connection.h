//
// Created by shniu on 18-8-31.
//

#ifndef METACHAIN_CONNECTION_H
#define METACHAIN_CONNECTION_H

#include <boost/enable_shared_from_this.hpp>

namespace metachain {

    // This class represents a connection to one other peer.
    class Connection : public boost::enable_shared_from_this<Connection> {

    };

}  // metachain

#endif //METACHAIN_CONNECTION_H
