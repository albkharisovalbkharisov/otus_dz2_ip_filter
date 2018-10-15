#define BOOST_TEST_MODULE ip_filter_test_module

#include "ip_filter.h"
#include <iostream>
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(ip_filter_test_suite)
ip_t ip1 = {15, 1, 17, 18};
ip_t ip2 = {1, 16, 17, 18};
ip_t ip3 = {9, 16, 1, 18};
ip_t ip4 = {0, 16, 17, 1};
ip_t ip5 = {0, 12, 7, 1};
ip_t ip6 = {0, 16, 17, 1};
ip_t ip7 = {0, 70, 17, 1};

//ip_t ip1 = {"15", "1", "17", "18"};
//ip_t ip2 = {"1", "16", "17", "18"};
//ip_t ip3 = {"9", "16", "1", "18"};
//ip_t ip4 = {"0", "16", "17", "1"};
//ip_t ip5 = {"0", "12", "7", "1"};
//ip_t ip6 = {"0", "16", "17", "1"};
//ip_t ip7 = {"0", "70", "17", "1"};

BOOST_AUTO_TEST_CASE(test_logic)
{
    ip_pool_t ipf;
    ip_pool_t ip_pool;
    ip_pool.reserve(4);
    ip_pool.emplace_back(ip1);
    ip_pool.emplace_back(ip2);
    ip_pool.emplace_back(ip3);
    ip_pool.emplace_back(ip4);
    ip_pool.emplace_back(ip5);
    ip_pool.emplace_back(ip6);
    ip_pool.emplace_back(ip7);


    ipf = filter(ip_pool, 1);
    BOOST_CHECK(ipf.size() == 1);

    ipf = filter(ip_pool, 16);
    BOOST_CHECK(ipf.size() == 0);

    ipf = filter(ip_pool, 0);
    BOOST_CHECK(ipf.size() == 4);


    ipf = filter(ip_pool, 0, 70);
    BOOST_CHECK(ipf.size() == 1);

    ipf = filter(ip_pool, 0, 16);
    BOOST_CHECK(ipf.size() == 2);

    ipf = filter(ip_pool, 15, 0);
    BOOST_CHECK(ipf.size() == 0);


    ipf = filter(ip_pool, 0, 70, 17);
    BOOST_CHECK(ipf.size() == 1);

    ipf = filter(ip_pool, 0, 16, 17);
    BOOST_CHECK(ipf.size() == 2);

    ipf = filter(ip_pool, 15, 0, 17);
    BOOST_CHECK(ipf.size() == 0);


    ipf = filter(ip_pool, 0, 70, 17, 1);
    BOOST_CHECK(ipf.size() == 1);

    ipf = filter(ip_pool, 0, 16, 17, 1);
    BOOST_CHECK(ipf.size() == 2);

    ipf = filter(ip_pool, 15, 1, 17, 19);
    BOOST_CHECK(ipf.size() == 0);


    // assert fails here
//    ipf = filter(ip_pool, 0, 70, 17, 1, 0);
//    BOOST_CHECK(ipf.size() == 1);
//
//    ipf = filter(ip_pool, 0, 16, 17, 1, 999);
//    BOOST_CHECK(ipf.size() == 2);
//
//    ipf = filter(ip_pool, 15, 1, 17, 19, 9999);
//    BOOST_CHECK(ipf.size() == 0);


    ipf = filter_any(ip_pool, 18);
    BOOST_CHECK(ipf.size() == 3);

    ipf = filter_any(ip_pool, 1);
    BOOST_CHECK(ipf.size() == 7);

    ipf = filter_any(ip_pool, 99);
    BOOST_CHECK(ipf.size() == 0);

}

BOOST_AUTO_TEST_SUITE_END()

