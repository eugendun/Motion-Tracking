#pragma once

#include "Test_MotionUnit.h"

#include <boost/test/included/unit_test.hpp>
#include <boost/bind.hpp>

using namespace boost::unit_test;

test_suite* init_unit_test_suite(int argc, char* argv[]) {
	boost::shared_ptr<Test_MotionUnit> tester(new Test_MotionUnit);

	framework::master_test_suite().add(BOOST_TEST_CASE(boost::BOOST_BIND(&Test_MotionUnit::test_InitialState, tester)));
	framework::master_test_suite().add(BOOST_TEST_CASE(boost::BOOST_BIND(&Test_MotionUnit::test_SimpleSetterGetter, tester)));
	framework::master_test_suite().add(BOOST_TEST_CASE(boost::BOOST_BIND(&Test_MotionUnit::test_ChildParentRelationship, tester)));

	return 0;
}
