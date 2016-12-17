#pragma once
#include <cstdint>

namespace framework
{

using Identity = int64_t;

Identity getMyIdentity();
void initializeIdentity(int addon = 0);

}
