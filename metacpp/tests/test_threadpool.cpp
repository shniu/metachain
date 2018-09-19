//
// Created by shniu on 18-9-19.
//

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "MetaCTest"

#include <iostream>
#include <string>
#include <chrono>
#include <mutex>
#include <boost/test/unit_test.hpp>
#include <boost/test/output_test_stream.hpp>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
#include <boost/lexical_cast.hpp>
#include "utility/threadpool.h"

struct cout_redirect {
    cout_redirect(std::streambuf * new_buf)
            : old(std::cout.rdbuf(new_buf)) {
    }

    ~cout_redirect() {
        std::cout.rdbuf(old);
    }

private:
    std::streambuf * old;
};

BOOST_AUTO_TEST_SUITE(threadpool)


    BOOST_AUTO_TEST_CASE(pool_size) {
        metachain::threadpool pool(4);
        BOOST_CHECK(pool.size() == 4);
    }

    BOOST_AUTO_TEST_CASE(pool_io_service) {
        /// multi threads use only one io_service

        metachain::threadpool pool(3);
        BOOST_CHECK(!pool.empty());

        boost::asio::steady_timer t1{pool.io_service(), std::chrono::seconds(2)};
        boost::asio::steady_timer t2{pool.io_service(), std::chrono::seconds(2)};

        int value = 0;
        std::mutex mtx;
        boost::test_tools::output_test_stream output;

        auto fcn = [&mtx, &value, &output](const boost::system::error_code& ec){
            std::lock_guard<std::mutex> lock_guard(mtx);

            auto thread_id = boost::lexical_cast<std::string>(boost::this_thread::get_id());
            std::cout << thread_id << " in threadpool, value=" << ++value << std::endl;

        };

        t1.async_wait(fcn);
        t2.async_wait(fcn);

        pool.shutdown();
    }

BOOST_AUTO_TEST_SUITE_END()

