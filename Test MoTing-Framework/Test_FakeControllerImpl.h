#pragma once

#include <MoTingLib.h>
#include <FakeControllerImpl.h>
#include <boost/test/included/unit_test.hpp>
#include <iostream>

class Test_FakeControllerImpl
{
public:
	void test_FindMotionUnits() {
		MotionUnitList mus = ctrl.findMotionUnits();
		BOOST_REQUIRE(mus.size() == FakeControllerImpl::SensorNumber);
	}

	void test_TareWithQuaternion() {
		// TODO
	}
	
	void test_ControllTracking() {
		MotionUnitList mus = ctrl.findMotionUnits();
		string sid = mus[0]->getId();
		Quaternion oldOrientation;

		oldOrientation = mus[0]->getOrientation();
		boost::this_thread::sleep(boost::posix_time::microsec(10));
		BOOST_REQUIRE(oldOrientation == mus[0]->getOrientation());

		ctrl.startTracking(sid);
		oldOrientation = mus[0]->getOrientation();
		boost::this_thread::sleep(boost::posix_time::millisec(10));
		BOOST_REQUIRE(oldOrientation != mus[0]->getOrientation());

		// TODO: test stopTracking
	}

private:
	FakeControllerImpl ctrl;
};