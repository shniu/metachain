//
// Created by shniu on 18-9-19.
//

#ifndef METACHAIN_ENDPOINT_H
#define METACHAIN_ENDPOINT_H

#include <string>
#include <vector>
#include "asio.h"

namespace metachain {

    /**
     * Helper for a network endpoint in URI format.
     * This is a container for a {scheme, host, port} tuple.
     */
    class endpoint {
    public:
        // endpoint list with a vector
        typedef std::vector<endpoint> list;

        /**
         * Default constructor
         */
        endpoint();

        /**
         * Copy constructor
         * @param[in] other  the object to copy into self on constructor
         */
        endpoint(const endpoint& other);

        /**
         * Init constructor
         * @param[in] value  like [scheme://]host[:port]
         */
        endpoint(const std::string& value);

        endpoint(const std::string& host, uint16_t port);
        endpoint(const std::string& scheme, const std::string& host, uint16_t port);

        endpoint(const asio::endpoint& asio_endpoint);
        endpoint(const asio::address& address, uint16_t port);

    private:
        std::string m_scheme;
        std::string m_host;
        uint16_t m_port;
    };
}

#endif //METACHAIN_ENDPOINT_H
