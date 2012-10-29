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

void computeOrientations(SensorMotionUnitMap* sensorMotionUnits) {
	while (true) {
		SensorMotionUnitMap::iterator it;
		MoTing::QuatGenerator quatGen;
		for (it = sensorMotionUnits->begin(); it != sensorMotionUnits->end(); it++) {
			it->second->setOrientation(quatGen.generate());
		}
		boost::this_thread::sleep(boost::posix_time::seconds(1));
	}
}

void FakeControllerImpl::tareWithQuaternion(const Quaternion& quat) {
	// TODO
}

void FakeControllerImpl::startTracking(const string& id) {
	boost::thread t(computeOrientations, &sensorMotionUnits);
}

void FakeControllerImpl::stopTracking(const string& id) {
	// TODO
}
