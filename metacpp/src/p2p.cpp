//
// Created by shniu on 18-9-17.
//

#include <network/p2p.h>

namespace metachain {
namespace network {

    p2p::p2p(settings &settings)
            : m_settings(settings) {
    }

    // shutdown network
    p2p::~p2p() {
        p2p::close();
    }

    // close
    // ----------
    void p2p::close() {
        // todo
    }

    void p2p::start() {
        // todo start the network
    }
}
}
