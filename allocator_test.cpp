/*
 * allocator_test.cpp
 *
 *  Created on: 19 мая 2019 г.
 *      Author: sveta
 */
#define BOOST_TEST_MODULE allocator_test_module
#include <boost/test/included/unit_test.hpp>
#include "ListAllocator.h"
#include "SimpleForwardList.h"
#include <map>

BOOST_AUTO_TEST_SUITE(allocator_test_suite)

BOOST_AUTO_TEST_CASE(allocator_rvalue_test_case)
{
	 auto list= SimpleForwardList<int>();
	 int i=0;
	 list.push_back(i);
	 i=2;
	 list.push_back(i);
	 BOOST_REQUIRE_EQUAL(*list.begin(),0);
	 BOOST_REQUIRE_EQUAL(*list.end(),2);
}

BOOST_AUTO_TEST_CASE(allocator_lvalue_test_case)
{
	 auto list= SimpleForwardList<int>();
	 list.push_back(0);
	 list.push_back(2);
	 BOOST_REQUIRE_EQUAL(*list.begin(),0);
	 BOOST_REQUIRE_EQUAL(*list.end(),2);
}

BOOST_AUTO_TEST_CASE(allocator_pop_test_case)
{
	 auto list= SimpleForwardList<int>();
	 list.push_back(0);
	 list.push_back(2);
	 list.pop_head();
	 BOOST_REQUIRE_EQUAL(*list.begin(),2);
}

BOOST_AUTO_TEST_SUITE_END()



