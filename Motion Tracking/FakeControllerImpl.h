#pragma once

#include "ImplController.h"
#include <vector>
#include <map>
#include <boost/thread.hpp>

using std::vector;
using std::map;
using std::pair;

class FakeSensor;

typedef map<string, MotionUnit*> SensorMotionUnitMap;

class FakeControllerImpl : public ImplController
{
public:
	static const int SensorNumber;

	FakeControllerImpl();
	~FakeControllerImpl();

	MotionUnitList& findMotionUnits();
	void tareWithQuaternion(const Quaternion& quat);
	void startTracking(const string& id);
	void stopTracking(const string& id);

private:
	MotionUnitList motionUnits;
	SensorMotionUnitMap sensorMotionUnits;
	Quaternion tareQuaternion;

	FakeControllerImpl(const FakeControllerImpl& rController);
	FakeControllerImpl& operator=(const FakeControllerImpl& rController);
};
