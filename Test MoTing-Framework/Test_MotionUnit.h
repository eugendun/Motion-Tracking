#pragma once

#include <MotionUnit.h>
#include <boost/test/included/unit_test.hpp>
#include <boost/random/uniform_01.hpp>

#include <boost/random/linear_congruential.hpp>

using namespace MoTing;

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

		Quaternion expOrientation = this->_getRandomQuaternion();
		m.setOrientation(expOrientation);
		BOOST_REQUIRE(m.getOrientation() == expOrientation);
	}


private:
	MotionUnit m;

	Quaternion _getRandomQuaternion() {
		boost::minstd_rand						intgen;
		boost::uniform_01<boost::minstd_rand>	gen(intgen);
		return Quaternion((float)gen(), (float)gen(), (float)gen(), (float)gen());
	}
};
