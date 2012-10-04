#pragma once

#include "ImplController.h"

class FakeControllerImpl : public ImplController
{
public:
	MotionUnitList findMotionUnits();
	void tareWithQuaternion(Quaternion quat);
	void startTracking(string id);
	void stopTracking(string id);

private:
	MotionUnitList motionUnits;
};
