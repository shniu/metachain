//
// Created by shniu on 18-9-17.
//

#ifndef METACHAIN_MESSAGE_H
#define METACHAIN_MESSAGE_H

#include <iostream>

namespace metachain {
namespace network {

    using namespace std;

    struct message_header {

    };

    class message {
    public:
        message();

        /// free resource
        virtual ~message() {
            free(m_payload);
        };

    private:
        message_header m_header;
        string m_guid;

        /// message payload data
        char * m_payload;
    };

}  // network
}  // metachain

#endif //METACHAIN_MESSAGE_H
