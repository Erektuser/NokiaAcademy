#pragma once
#include "../GlobalTestConfig.hpp"

#define TEST(test_case_name, test_name) __TEST(Engine, test_case_name, test_name)
#define TEST_F(test_case_name, test_name) __TEST_F(Engine, test_case_name, test_name)
