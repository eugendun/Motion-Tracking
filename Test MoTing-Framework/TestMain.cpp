#include <boost/test/included/unit_test.hpp>
#include <boost/bind.hpp>
#include <MotionUnit.h>

using namespace boost::unit_test;
using namespace MoTing;

class test_class
{
public:
	test_class()
		: mUnit_1(MotionUnit("Init_Id_1")),
		  mUnit_2(MotionUnit("Init_Id_2")) {}
	~test_class() {}

	MotionUnit mUnit_1, mUnit_2;

	void test_InitState() {
		BOOST_CHECK(mUnit_1.getId() == "Init_Id_1");
		BOOST_CHECK(mUnit_1.getOrientation() == Quaternion(0.0, 0.0, 0.0, 0.0));
		BOOST_CHECK(mUnit_1.getRelativeOrientation() == Quaternion(0.0, 0.0, 0.0, 0.0));
		BOOST_CHECK(mUnit_1.getParent() == 0);
		BOOST_CHECK(mUnit_1.getChilds().size() == 0);
	}

	void test_SetGetId() {
		mUnit_1.setId((string)"NewId_1");
		BOOST_CHECK(mUnit_1.getId() == "NewId_1");
	}

	void test_SetGetOrientation() {
		Quaternion temp(1.0, 0.0, 1.0, 0.0);
		mUnit_1.setOrientation(temp);
		BOOST_CHECK(mUnit_1.getOrientation() == temp);
	}

	void test_GetParentAddChildren() {
		mUnit_1.addChild(mUnit_2);
		Quaternion					temp = mUnit_1.getOrientation() * mUnit_2.getOrientation();
		MotionUnitList				list = mUnit_1.getChilds();
		bool						isIn = false;
		MotionUnitList::iterator	it_begin = list.begin();
		for (it_begin; it_begin != list.end(); it_begin++) {
			if (it_begin->getId() == mUnit_2.getId()) {
				isIn = true;
			}
		}

		//BOOST_REQUIRE(mUnit_2.getParent()->getId() == mUnit_1.getId());
		BOOST_CHECK(mUnit_2.getRelativeOrientation() == temp);
		BOOST_REQUIRE(isIn);

		mUnit_1.removeChildById(mUnit_2.getId());
		list = mUnit_1.getChilds();
		isIn = false;
		for (it_begin = list.begin(); it_begin != list.end(); it_begin++) {
			if (it_begin->getId() == mUnit_2.getId()) {
				isIn = true;
			}
		}
		BOOST_REQUIRE(!isIn);
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
	return 0;
}
