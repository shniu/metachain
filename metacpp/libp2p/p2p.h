//
// Created by shniu on 18-9-18.
//

#ifndef METACHAIN_P2P_H
#define METACHAIN_P2P_H

#include "utility/threadpool.h"

namespace metachain {
namespace network {

    /// This represent a network
    class p2p {
    public:
        p2p();

        /// Free resource
        ~p2p() {
            close();
        };

        /// Startup
        void start();

        /// Run
        void run();

        /// close
        void close();

        /// connect
        void connect();

    private:
        /// sessions
        /// hosts

        threadpool m_threadpool;
    };

}  // network
}  // metachain
#endif //METACHAIN_P2P_H
