#include "Utilities.hpp"
#include <netdb.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <ifaddrs.h>


namespace framework
{
int getHostAddress(const char * host)
{
    hostent * hostEntity = gethostbyname(host);
    std::string a = inet_ntoa (*(struct in_addr *)*(hostEntity->h_addr_list));
    return *((int*)hostEntity->h_addr);
}

int getLocalAddess()
{
    static int result = 0;

    if (!result)
    {
        getHostAddress("localhost");
    }

    return result;
}

}
