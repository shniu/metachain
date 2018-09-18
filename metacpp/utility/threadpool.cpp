//
// Created by shniu on 18-9-18.
//

#include "threadpool.h"

namespace metachain {

    threadpool::threadpool(size_t number_threads)
            : m_size(0) {
        spawn(number_threads);
    }

    threadpool::~threadpool() {
        shutdown();
        join();
    }

    bool threadpool::empty() const {
        return size() != 0;
    }

    size_t threadpool::size() const {
        return m_size.load();
    }

    void threadpool::spawn(size_t number_threads) {
        m_ios.reset();

        for (auto i = 0; i < number_threads; ++i) {
            spawn_once();
        }
    }

    void threadpool::spawn_once() {

        /// init asio io_service work
        m_work_mutex.lock_upgrade();
        if (!m_work_ptr) {
            m_work_mutex.unlock_upgrade_and_lock();
            m_work_ptr = std::make_shared<asio::io_service::work>(m_ios);
            m_work_mutex.unlock_and_lock_upgrade();
        }
        m_work_mutex.unlock_upgrade();

        /// ---

        boost::unique_lock<boost::shared_mutex> lock(m_threads_mutex);
        m_threads.emplace_back([this](){
            // this->m_ios.run();
            m_ios.run();
        });

        ++m_size;
    }

    void threadpool::abort() {
        m_ios.stop();
    }

    void threadpool::shutdown() {
        boost::unique_lock<boost::shared_mutex> lock(m_work_mutex);
        m_work_ptr.reset();
    }

    void threadpool::join() {
        boost::unique_lock<boost::shared_mutex> lock(m_threads_mutex);

        // const auto this_id = boost::this_thread::get_id();
        for (auto& thread : m_threads) {
            thread.join();
        }

        m_threads.clear();
        m_size.store(0);
    }

    asio::io_service& threadpool::io_service() {
        return m_ios;
    }

    const asio::io_service& threadpool::io_service() const {
        return m_ios;
    }

}

