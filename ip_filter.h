#pragma once

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using ip_t = std::vector<uint8_t>;
using ip_pool_t = std::vector<ip_t>;

ip_pool_t filter_any(const ip_pool_t &ip_pool, uint8_t num)
{
    ip_pool_t ipf;  // filtered
    for (auto ip : ip_pool)
    {
#if 0
        if (std::any_of(ip.cbegin(), ip.cend(), [num](unsigned char s) { return s == num; } ))
            ipf.push_back(ip);
#else
        if (ip.end() != std::find(ip.begin(), ip.end(), num))
            ipf.push_back(ip);
#endif // 1
    }
    return ipf;
}

template <typename... Args>
ip_pool_t filter(const ip_pool_t &ip_pool, Args... args)
{
    std::vector<int> a{args...};
    static_assert(sizeof...(Args) <= 4, "filter gets 4 parameters max + ip_pool");

    ip_pool_t ipf;  // filtered

    for (auto ip : ip_pool)
    {
        if (std::equal(a.begin(), a.end(), ip.begin()))
            ipf.push_back(ip);
    }

    return ipf;
}

