#include "FakeControllerImpl.h"

#include <boost/lexical_cast.hpp>
#include <boost/date_time.hpp>

void generateOrientation(FakeSensor& sensor) {
	boost::posix_time::seconds sleepTime(1);
	while (true) {
		try {
			boost::this_thread::interruption_point();
		} catch (const boost::thread_interrupted&) {
			break;
		}

		sensor.setOrientation(MoTing::getRandomQuaternion());
		boost::this_thread::sleep(sleepTime);
	}
}

string getSensorId(int i) {
	return string("sensor_").append(boost::lexical_cast<string>(i));
}

const int FakeControllerImpl::SensorNumber = 10;

FakeControllerImpl::FakeControllerImpl() {
	for (int i = 0; i < SensorNumber; i++) {
		string sensorId(getSensorId(i));
		sensorWorkers[sensorId].first = FakeSensor();
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

MotionUnitList FakeControllerImpl::findMotionUnits() {
	MotionUnitList motionUnits;
	SensorMotionUnitMap::iterator it;
	for (it = sensorMotionUnits.begin(); it != sensorMotionUnits.end(); it++) {
		motionUnits.push_back(it->second);
	}

	return motionUnits;
}

void FakeControllerImpl::tareWithQuaternion(Quaternion quat) {
	// TODO
}

void FakeControllerImpl::startTracking(string id) {
	FakeSensorWorkerMap::iterator it = sensorWorkers.find(id);
	if (it != sensorWorkers.end()) {
		it->second.second = boost::thread(generateOrientation, it->second.first);
	}
}

void FakeControllerImpl::stopTracking(string id) {
	FakeSensorWorkerMap::iterator it = sensorWorkers.find(id);
	if (it != sensorWorkers.end()) {
		it->second.second.interrupt();
	}
}

void FakeSensor::setOrientation(Quaternion orientation) {
	this->orientation = orientation;
}

Quaternion FakeSensor::getOrientation() {
	return orientation;
}
