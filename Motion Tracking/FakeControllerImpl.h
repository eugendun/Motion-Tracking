#pragma once

#include "ImplController.h"
#include <vector>
#include <map>
#include <boost/thread.hpp>

using std::vector;
using std::map;
using std::pair;

class FakeSensor;

// map<SensorID, <FakeSensor, ThreadID>>
typedef map<string, pair<FakeSensor,boost::thread>> FakeSensorWorkerMap;
typedef map<string, MotionUnit*> SensorMotionUnitMap;

class FakeControllerImpl : public ImplController
{
public:
	static const int SensorNumber;

	FakeControllerImpl();
	~FakeControllerImpl();

	MotionUnitList findMotionUnits();
	void tareWithQuaternion(Quaternion quat);
	void startTracking(string id);
	void stopTracking(string id);

private:
	FakeSensorWorkerMap sensorWorkers;
	SensorMotionUnitMap sensorMotionUnits;
	Quaternion tareQuaternion;
};

class FakeSensor
{
public:
	void setOrientation(Quaternion orientation);
	Quaternion getOrientation();

private:
	Quaternion orientation;
};