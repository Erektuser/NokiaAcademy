#include "Identity.hpp"
#include <time.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>

namespace framework
{

namespace
{
const Identity NOT_SET = 0;
const char * IDENTITY_FILE = "identity";
Identity identity;

Identity getExistingIdentity()
{
    std::cout << "getExisting" << std::endl;
    Identity identity = NOT_SET;
    std::ifstream file;
    file.exceptions ( std::ifstream::failbit | std::ifstream::badbit );
    try
    {
        file.open (IDENTITY_FILE, std::ios::in | std::ios::binary);
        if (!file.read (reinterpret_cast<char*>(&identity), sizeof(identity)))
        {
            identity = NOT_SET;
        }
        file.close();
    }
    catch (std::ifstream::failure){}

    return identity;
}

Identity generateNewIdentity()
{
    std::srand(time(0));
    int size = sizeof(Identity)/sizeof(int);
    volatile Identity identity {};

    for (int i = 0; i < size; ++i)
    {
        reinterpret_cast<volatile int*>(&identity)[i] = std::rand();
    }
    std::cout << "Generated new identity " << identity << std::endl;
    return identity;
}

void saveIdentity(Identity identity)
{
    std::fstream file;
    file.exceptions ( std::ifstream::failbit | std::ifstream::badbit );
    try
    {
        file.open (IDENTITY_FILE, std::ios::out | std::ios::binary);
        file.write(reinterpret_cast<char*>(&identity), sizeof(identity));
        file.close();
    }
    catch (std::ifstream::failure){}
}

}


Identity getMyIdentity()
{
    if (identity == NOT_SET)
    {
        std::cerr << "Error: Uninitialized identity" << std::endl;
    }
    return identity;
}

void initializeIdentity(int addon)
{
    if (identity == NOT_SET)
    {
        identity = getExistingIdentity();
        if (identity == NOT_SET)
        {
            identity = generateNewIdentity();
            saveIdentity(identity);
        }
        std::cout << "Generated identity " << identity << std::endl;
        identity += addon;
        std::cout << "Used identity " << identity << std::endl;
    }
    else
    {
        std::cerr << "Error: try to reinitialize identity" << std::endl;
    }
}

}
