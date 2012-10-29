#pragma once

#include "ImplController.h"

class YostControllerImpl : public ImplController
{
public:
	MotionUnitList& findMotionUnits();
	void tareWithQuaternion(const Quaternion& quat);
	void startTracking(const string& id);
	void stopTracking(const string& id);

private:
	MotionUnitList motionUnits;
};
