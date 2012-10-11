#pragma once

#include <MoTingLib.h>
#include <MotionUnit.h>
#include <boost/test/included/unit_test.hpp>

class Test_MotionUnit
{
public:
	Test_MotionUnit()
		: m(MotionUnit("m")) {}
	~Test_MotionUnit() {}

	void test_Constructors() {
		BOOST_CHECK(m.getId() == "m");
		BOOST_CHECK(m.getOrientation() == Quaternion(0.0, 0.0, 0.0, 0.0));
	}

	void test_SimpleSetterGetter() {
		m.setId((string)"new_m");
		BOOST_REQUIRE(m.getId() == "new_m");
		m.setId((string)"m");
		BOOST_REQUIRE(m.getId() == "m");

		Quaternion expOrientation = MoTing::getRandomQuaternion();
		m.setOrientation(expOrientation);
		BOOST_REQUIRE(m.getOrientation() == expOrientation);
	}


private:
	MotionUnit m;
};
