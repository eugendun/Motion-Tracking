#pragma once

#include "Test_MotionUnit.h"
#include "Test_Bone.h"
#include "Test_FakeControllerImpl.h"

#include <boost/test/included/unit_test.hpp>
#include <boost/bind.hpp>

using namespace boost::unit_test;

test_suite* init_unit_test_suite(int argc, char* argv[]) {
	boost::shared_ptr<Test_MotionUnit>	tester(new Test_MotionUnit);
	framework::master_test_suite().add(BOOST_TEST_CASE(boost::BOOST_BIND(&Test_MotionUnit::test_Constructors, tester)));
	framework::master_test_suite().add(BOOST_TEST_CASE(boost::BOOST_BIND(&Test_MotionUnit::test_SimpleSetterGetter, tester)));

	boost::shared_ptr<Test_Bone>		testBone(new Test_Bone);
	framework::master_test_suite().add(BOOST_TEST_CASE(boost::BOOST_BIND(&Test_Bone::test_Constructors, testBone)));
	framework::master_test_suite().add(BOOST_TEST_CASE(boost::BOOST_BIND(&Test_Bone::test_AttachDetach, testBone)));
	framework::master_test_suite().add(BOOST_TEST_CASE(boost::BOOST_BIND(&Test_Bone::test_AddRemoveChild, testBone)));

	boost::shared_ptr<Test_FakeControllerImpl> testerFakeController(new Test_FakeControllerImpl);
	framework::master_test_suite().add(BOOST_TEST_CASE(boost::BOOST_BIND(&Test_FakeControllerImpl::test_FindMotionUnits, testerFakeController)));

	return 0;
}
