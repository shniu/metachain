//
// Created by shniu on 18-9-18.
//

#ifndef METACHAIN_MESSAGE_H
#define METACHAIN_MESSAGE_H

#include <iostream>

using namespace std;

namespace metachain {
namespace network {

    class message {
    public:
        message();

    private:
        /// message guid
        string m_guid;

        /// message payload
        char * m_payload;
    };

}
}

#endif //METACHAIN_MESSAGE_H
