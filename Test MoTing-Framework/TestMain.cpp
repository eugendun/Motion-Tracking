#include <boost/test/included/unit_test.hpp>
#include <boost/bind.hpp>
#include <MotionUnit.h>

using namespace boost::unit_test;
using namespace MoTing;

class test_class
{
public:
	test_class()
		: m1(MotionUnit("m1")),
		  m2(MotionUnit("m2")),
		  m3("m3") {}
	~test_class() {}

	MotionUnit m1, m2, m3;

	void test_InitState() {
		BOOST_CHECK(m1.getId() == "m1");
		BOOST_CHECK(m1.getOrientation() == Quaternion(0.0, 0.0, 0.0, 0.0));
		BOOST_CHECK(m1.getRelativeOrientation() == Quaternion(0.0, 0.0, 0.0, 0.0));
		BOOST_CHECK(m1.getParent() == 0);
		BOOST_CHECK(m1.getChilds().empty());
	}

	void test_SetGetId() {
		m1.setId((string)"new_m1");
		BOOST_REQUIRE(m1.getId() == "new_m1");
		m1.setId((string)"m1");
		BOOST_REQUIRE(m1.getId() == "m1");
	}

	void test_SetGetOrientation() {
		Quaternion temp(1.0, 0.0, 1.0, 0.0);
		m1.setOrientation(temp);
		BOOST_REQUIRE(m1.getOrientation() == temp);
	}

	void test_GetParentAddChildren() {
		m1.addChild(m2);
		BOOST_REQUIRE(this->_isIn(m2, m1.getChilds()));
		BOOST_REQUIRE(m2.getParent());
		BOOST_REQUIRE(m2.getParent()->getId() == m1.getId());

		Quaternion temp = m1.getOrientation() * m2.getOrientation();
		BOOST_REQUIRE(m2.getRelativeOrientation() == temp);

		m1.removeChildById(m2.getId());
		BOOST_REQUIRE(!this->_isIn(m2, m1.getChilds()));
		BOOST_REQUIRE(!m2.getParent());
	}

	// 1. m1 and m2 has no children. 
	// 2. m3 will be added to m2. => m3 is a child of m2 and m2 has a child m3.
	// 3. m3 will be added to m1. => m3 is not a child of m2 anymore and m2 has no child m3,
	//								 m3 is a child of m1 and m1 has a child m3.
	// 4. m2 will be added to m3. => m2 is a child of m3 and m3 has a child m2.
	//								 the relative orientation o of m2 can be calculated with m1.o * m3.o * m2.o
	void test_ChildParentRelationship_2() {
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
		m3.addChild(m2);
		BOOST_REQUIRE(this->_isIn(m2, m3.getChilds()));
		BOOST_REQUIRE(m2.getParent() && m2.getParent()->getId() == m3.getId());
		Quaternion expOrientation = m1.getOrientation() * m3.getOrientation() * m2.getOrientation();
		BOOST_REQUIRE(m2.getRelativeOrientation() == expOrientation);
	}

private:
	bool _isIn(MotionUnit& m, MotionUnitList& list) {
		MotionUnitList::iterator it_begin = list.begin();
		for (it_begin; it_begin != list.end(); it_begin++) {
			if (it_begin->getId() == m.getId()) {
				return true;
			}
		}
		return false;
	}
};


test_suite* init_unit_test_suite(int argc, char* argv[]) {
	boost::shared_ptr<test_class> tester(new test_class);

	framework::master_test_suite().add(BOOST_TEST_CASE(boost::BOOST_BIND(&test_class::test_InitState, tester)));
	framework::master_test_suite().add(BOOST_TEST_CASE(boost::BOOST_BIND(&test_class::test_SetGetId, tester)));
	framework::master_test_suite().add(BOOST_TEST_CASE(boost::BOOST_BIND(&test_class::test_SetGetOrientation,
																		 tester)));
	framework::master_test_suite().add(BOOST_TEST_CASE(boost::BOOST_BIND(&test_class::test_GetParentAddChildren,
																		 tester)));
	framework::master_test_suite().add(BOOST_TEST_CASE(boost::BOOST_BIND(&test_class::test_ChildParentRelationship_2,
																		 tester)));
	return 0;
}
