#include "FakeControllerImpl.h"

#include <boost/lexical_cast.hpp>
#include <boost/date_time.hpp>

string getSensorId(int i) {
	return string("sensor_").append(boost::lexical_cast<string>(i));
}

const int FakeControllerImpl::SensorNumber = 10;

FakeControllerImpl::FakeControllerImpl() {
	for (int i = 0; i < SensorNumber; i++) {
		string sensorId(getSensorId (i));
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

MotionUnitList FakeControllerImpl::findMotionUnits() {
	MotionUnitList					motionUnits;
	SensorMotionUnitMap::iterator	it;
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
		it->second.Start();
	}
}

void FakeControllerImpl::stopTracking(string id) {
	FakeSensorWorkerMap::iterator it = sensorWorkers.find(id);
	if (it != sensorWorkers.end()) {
		it->second.Stop();
	}
}

FakeSensor::FakeSensor() {
	m_thread = NULL;
	m_mustStop = false;
}

FakeSensor::~FakeSensor() {
	if (m_thread != NULL) {
		delete m_thread;
	}
}

void FakeSensor::Start() {
	m_thread = new boost::thread(boost::ref(*this));
}

void FakeSensor::Stop() {
	m_mustStopMutex.lock();
	m_mustStop = true;
	m_mustStopMutex.unlock();

	if (m_thread != NULL) {
		m_thread->join();
	}
}

void FakeSensor::operator()() {
	bool mustStop;
	do {
		setOrientation(MoTing::getRandomQuaternion());
		boost::this_thread::sleep(boost::posix_time::seconds(1));
		m_mustStopMutex.lock();
		mustStop = m_mustStop;
		m_mustStopMutex.unlock();
	} while (mustStop == false);
}

void FakeSensor::setOrientation(Quaternion orientation) {
	this->orientation = orientation;
}

Quaternion FakeSensor::getOrientation() {
	return orientation;
}
