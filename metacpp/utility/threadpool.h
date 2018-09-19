//
// Created by shniu on 18-9-18.
//

#ifndef METACHAIN_THREADPOOL_H
#define METACHAIN_THREADPOOL_H

#include <atomic>
#include <vector>
#include "asio.h"
#include "noncopyable.h"

namespace metachain {

    /// asio io_service thread pool
    /// https://senlinzhan.github.io/2017/09/17/boost-asio/
    class threadpool
            : noncopyable {
    public:

        threadpool(size_t number_threads=0);
        ~threadpool();

        /// empty or not
        bool empty() const;

        /// size
        size_t size() const;

        /// spawn
        void spawn(size_t number_threads=1);

        /// abort, avoiding call
        void abort();

        /// destroy the work keep alive, allowing threads are joined
        void shutdown();

        /// wait for all threads join
        void join();

        /// get asio io_service
        asio::io_service& io_service();
        const asio::io_service& io_service() const ;

    private:
        void spawn_once();

        asio::io_service m_ios;

        std::atomic<size_t> m_size;
        std::vector<asio::thread> m_threads;
        boost::upgrade_mutex m_threads_mutex;

        /// work, lock free use strand if wanted
        std::shared_ptr<asio::io_service::work> m_work_ptr;
        boost::upgrade_mutex m_work_mutex;
    };

}

#endif //METACHAIN_THREADPOOL_H
