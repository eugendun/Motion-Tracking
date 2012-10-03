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
		: m1(MotionUnit("m1")),
		  m2(MotionUnit("m2")),
		  m3(MotionUnit("m3")) {}
	~Test_MotionUnit() {}

	void test_InitialState() {
		BOOST_CHECK(m1.getId() == "m1");
		BOOST_CHECK(m1.getOrientation() == Quaternion(0.0, 0.0, 0.0, 0.0));
		BOOST_CHECK(m1.getRelativeOrientation() == Quaternion(0.0, 0.0, 0.0, 0.0));
		BOOST_CHECK(m1.getParent() == 0);
		BOOST_CHECK(m1.getChilds().empty());
	}

	void test_SimpleSetterGetter() {
		m1.setId((string)"new_m1");
		BOOST_REQUIRE(m1.getId() == "new_m1");
		m1.setId((string)"m1");
		BOOST_REQUIRE(m1.getId() == "m1");

		Quaternion expOrientation = this->_getRandomQuaternion();
		m1.setOrientation(expOrientation);
		BOOST_REQUIRE(m1.getOrientation() == expOrientation);
	}

	// 1. m1 and m2 has no children. 
	// 2. m3 will be added to m2. => m3 is a child of m2 and m2 has a child m3.
	// 3. m3 will be added to m1. => m3 is not a child of m2 anymore and m2 has no child m3,
	//								 m3 is a child of m1 and m1 has a child m3.
	// 4. m2 will be added to m3. => m2 is a child of m3 and m3 has a child m2.
	//								 the relative orientation o of m2 can be calculated with m1.o * m3.o * m2.o
	// 5. m3 remove from m1 => m3 is not a child of m1 anymore and m1 has no child m3
	//								 the relative orientation o of m2 can be calculated with m3.0 * m3.o
	void test_ChildParentRelationship() {
		m1.addChild(m2);
		BOOST_REQUIRE(this->_isIn(m2, m1.getChilds()));
		BOOST_REQUIRE(m2.getParent());
		BOOST_REQUIRE(m2.getParent()->getId() == m1.getId());

		m1.setOrientation(this->_getRandomQuaternion());
		m2.setOrientation(this->_getRandomQuaternion());
		Quaternion expOrientation = m1.getOrientation() * m2.getOrientation();
		BOOST_REQUIRE(m2.getRelativeOrientation() == expOrientation);

		m1.removeChildById(m2.getId());
		BOOST_REQUIRE(!this->_isIn(m2, m1.getChilds()));
		BOOST_REQUIRE(!m2.getParent());

		// 1.
		BOOST_REQUIRE(m1.getChilds().empty());
		BOOST_REQUIRE(m2.getChilds().empty());
		BOOST_REQUIRE(m3.getChilds().empty());
		BOOST_REQUIRE(!m1.getParent());
		BOOST_REQUIRE(!m2.getParent());
		BOOST_REQUIRE(!m3.getParent());

		// 2.
		m2.addChild(m3);
		BOOST_REQUIRE(this->_isIn(m3, m2.getChilds()));
		BOOST_REQUIRE(m3.getParent() && m3.getParent()->getId() == m2.getId());

		// 3.
		m1.addChild(m3);
		BOOST_REQUIRE(!this->_isIn(m3, m2.getChilds()));
		BOOST_REQUIRE(m3.getParent() && m3.getParent()->getId() != m2.getId());
		BOOST_REQUIRE(this->_isIn(m3, m1.getChilds()));
		BOOST_REQUIRE(m3.getParent() && m3.getParent()->getId() == m1.getId());

		// 4.
		m1.setOrientation(this->_getRandomQuaternion());
		m2.setOrientation(this->_getRandomQuaternion());
		m3.setOrientation(this->_getRandomQuaternion());
		m3.addChild(m2);
		BOOST_REQUIRE(this->_isIn(m2, m3.getChilds()));
		BOOST_REQUIRE(m2.getParent() && m2.getParent()->getId() == m3.getId());
		expOrientation = m1.getOrientation() * m3.getOrientation() * m2.getOrientation();
		BOOST_REQUIRE(m2.getRelativeOrientation() == expOrientation);

		// 5.
		m1.removeChildById(m3.getId());
		BOOST_REQUIRE(!this->_isIn(m3, m1.getChilds()));
		BOOST_REQUIRE(!m3.getParent());
		expOrientation = m3.getOrientation() * m2.getOrientation();
		BOOST_REQUIRE(m2.getRelativeOrientation() == expOrientation);
	}

private:
	MotionUnit m1, m2, m3;

	bool _isIn(MotionUnit& m, MotionUnitList& list) {
		MotionUnitList::iterator it = list.begin();
		for (it; it != list.end(); it++) {
			if ((*it)->getId() == m.getId()) {
				return true;
			}
		}
		return false;
	}

	Quaternion _getRandomQuaternion() {
		boost::minstd_rand						intgen;
		boost::uniform_01<boost::minstd_rand>	gen(intgen);
		return Quaternion((float)gen(), (float)gen(), (float)gen(), (float)gen());
	}
};
