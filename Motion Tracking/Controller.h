#pragma once
#include <vector>
#include "MotionUnit.h"

using std::vector;

class Controller
{
	virtual vector<MotionUnit>& getMotionUnits() = 0;
	virtual void startTracking(MotionUnit& mUnit) = 0;
	virtual void stopTracking(MotionUnit& mUnit) = 0;
	virtual void tare(MotionUnit& mUnit) = 0;
};
