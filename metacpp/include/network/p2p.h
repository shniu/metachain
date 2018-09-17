//
// Created by shniu on 18-9-17.
//

#ifndef METACHAIN_P2P_H
#define METACHAIN_P2P_H

#include "network/define.h"
#include "network/settings.h"

namespace metachain {
namespace network {

    /// peer to peer network
    class p2p {

    public:
        p2p(settings &settings);

        ~p2p();

        /// close the p2p network
        void close();

        void start();

    private:
        settings m_settings;

    };

}  // network
}  // metachain

#endif //METACHAIN_P2P_H
