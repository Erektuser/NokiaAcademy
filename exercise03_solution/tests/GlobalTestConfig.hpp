#pragma once
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#ifdef TEST 
	#undef TEST
#endif

#ifdef TEST_F
	#undef TEST_F
#endif

#define __TEST(module, test_case_name, test_name) \
  GTEST_TEST_( module##_##test_case_name, test_name, \
              ::testing::Test, ::testing::internal::GetTestTypeId())
			  
#define __TEST_F(module, test_fixture, test_name) \
  GTEST_TEST_( module##_##test_fixture, test_name, test_fixture, \
              ::testing::internal::GetTypeId<test_fixture>())

