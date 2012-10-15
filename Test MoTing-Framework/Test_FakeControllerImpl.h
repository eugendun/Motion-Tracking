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
		BOOST_CHECK(mus.size() == FakeControllerImpl::SensorNumber);
		string sid = mus[0]->getId();
		ctrl.startTracking(sid);
		while (true) {
			Quaternion test = mus[0]->getOrientation();
			boost::this_thread::sleep(boost::posix_time::seconds(1));
		}
	}
	void test_TareWithQuaternion() {}
	void test_StartTracking() {}
	void test_StopTracking() {}

private:
	FakeControllerImpl ctrl;
};