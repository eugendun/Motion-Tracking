#include "FakeControllerImpl.h"

#include <boost/lexical_cast.hpp>
#include <boost/date_time.hpp>

string getIdAsString(int i) {
	return string("sensor_").append(boost::lexical_cast<string>(i));
}

const int FakeControllerImpl::SensorNumber = 10;

FakeControllerImpl::FakeControllerImpl()
	: tareQuaternion(Quaternion(0.0, 0.0, 0.0, 0.0)) {
	for (int i = 0; i < SensorNumber; i++) {
		string sensorId(getIdAsString (i));
		sensorWorkers[sensorId] = FakeSensor();
		sensorMotionUnits[sensorId] = new MotionUnit(sensorId);
	}
}

FakeControllerImpl::~FakeControllerImpl() {
	if (sensorMotionUnits.empty()) {
		return;
	}

	SensorMotionUnitMap::iterator it;
	for (it = sensorMotionUnits.begin(); it != sensorMotionUnits.end(); it++) {
		delete it->second;
	}
}

MotionUnitList& FakeControllerImpl::findMotionUnits() {
	SensorMotionUnitMap::iterator	it;
	for (it = sensorMotionUnits.begin(); it != sensorMotionUnits.end(); it++) {
		motionUnits.push_back(it->second);
	}
	return motionUnits;
}

void FakeControllerImpl::tareWithQuaternion(const Quaternion& quat) {
	// TODO
}

void FakeControllerImpl::startTracking(const string& id) {
	FakeSensorWorkerMap::iterator it = sensorWorkers.find(id);
	if (it != sensorWorkers.end()) {
		it->second.start();	
	}
}

void FakeControllerImpl::stopTracking(const string& id) {
	FakeSensorWorkerMap::iterator it = sensorWorkers.find(id);
	if (it != sensorWorkers.end()) {
		
	}
}

FakeSensor::FakeSensor()
	: orientation(Quaternion(0.0, 0.0, 0.0, 0.0)) {}

FakeSensor::~FakeSensor() {}

FakeSensor::FakeSensor(const FakeSensor& rSensor)
	: orientation(rSensor.orientation) {}

FakeSensor& FakeSensor::operator=(const FakeSensor& rSensor) {
	orientation = rSensor.orientation;
	return *this;
}

void FakeSensor::setOrientation(const Quaternion& rOrientation) {
	orientation = rOrientation;
}

Quaternion& FakeSensor::getOrientation() {
	return orientation;
}

void myThreads(FakeSensor& sensor) {
	while (true) {
		sensor.setOrientation(MoTing::getRandomQuaternion());
		boost::this_thread::yield();
	}
}

void FakeSensor::start() {
	t = boost::thread(myThreads, *this);
}

void FakeSensor::stop() {

}
