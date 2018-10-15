#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "ip_filter.h"

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
auto split(const std::string &str, char d)
{
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));
        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

void printIpPool(const ip_pool_t &v)
{
    for(const auto &ip : v)
    {
        for (auto ip_part = ip.cbegin(); ip_part != ip.cend() ; ++ip_part)
        {
            if (ip_part != ip.cbegin())
                std::cout << ".";
            std::cout << (unsigned)(*ip_part);
        }
        std::cout << std::endl;
    }
}

int main(int argc, char const *argv[])
{
    (void) argc;    // suppress warnings
    (void) argv;    // suppress warnings

    try
    {
        ip_pool_t ip_pool;
        for(std::string line; std::getline(std::cin, line);)
        {
            auto v = split(line, '\t');
            v = split(v.at(0), '.');
            ip_t ip;
            ip.reserve(4);
            std::for_each(v.begin(), v.end(), [&ip] ( const std::string &s ) { ip.push_back(std::stoi(s)); } );
            ip_pool.push_back(ip);
        }

        // TODO reverse lexicographically sort
        std::sort(ip_pool.begin(), ip_pool.end(), std::greater<std::vector<unsigned char>>());
        printIpPool(ip_pool);

        auto ipfiltered = filter(ip_pool, 1);
        printIpPool(ipfiltered);
        ipfiltered = filter(ip_pool, 46, 70);       // std::move implicitly, do we need to overload?
        printIpPool(ipfiltered);
        ipfiltered = filter_any(ip_pool, 46);       // std::move implicitly
        printIpPool(ipfiltered);
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}

