#pragma once

#include "ImplController.h"
#include <vector>
#include <map>
#include <boost/thread.hpp>

using std::vector;
using std::map;
using std::pair;

class FakeSensor;

typedef map<string, FakeSensor> FakeSensorWorkerMap;
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
	FakeSensorWorkerMap sensorWorkers;
	SensorMotionUnitMap sensorMotionUnits;
	Quaternion tareQuaternion;

	FakeControllerImpl(const FakeControllerImpl& rController);
	FakeControllerImpl& operator=(const FakeControllerImpl& rController);
};

/**
 *  ================================================
 */

class FakeSensor
{
public:
	FakeSensor();
	~FakeSensor();
	FakeSensor(const FakeSensor& rSensor);
	FakeSensor& operator=(const FakeSensor& rSensor);

	void setOrientation(const Quaternion& rOrientation);
	Quaternion& getOrientation();

	void start();
	void stop();

private:
	Quaternion orientation;
	boost::thread t;
};
