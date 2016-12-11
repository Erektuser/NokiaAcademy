#pragma once
#include "../GlobalTestConfig.hpp"

#define TEST(test_case_name, test_name) __TEST(Solution, test_case_name, test_name)
#define TEST_F(test_case_name, test_name) __TEST_F(Solution, test_case_name, test_name)
