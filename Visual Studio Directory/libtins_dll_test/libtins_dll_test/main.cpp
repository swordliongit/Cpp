#include <tins/tins.h>
// #include "include/tins/tins.h"
#include <iostream>

using namespace Tins;

int main()
{
    std::cout << "Starting..";
    EthernetII eth;
    IP* ip = new IP();
    TCP* tcp = new TCP();

    // tcp is ip's inner pdu
    ip->inner_pdu(tcp);

    // ip is eth's inner pdu
    eth.inner_pdu(ip);

    std::cout << "Ending..";
}