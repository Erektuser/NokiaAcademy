#pragma once

#include <Identity.hpp>
#include <string>

namespace tests
{
const char * createExitMessage();

const char * createNonExitMessage();

const char * createExitMessageWithWrongEndian();

const char * createIncomingTextMessage(framework::Identity identity, const std::string & text);
}
