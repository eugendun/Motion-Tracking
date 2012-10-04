#pragma once

#include "MotionUnit.h"
#include "MoTingLib.h"
#include <vector>
#include <string>

using MoTing::Quaternion;

class ImplController
{
public:
	virtual MotionUnitList findMotionUnits() = 0;
	virtual void tareWithQuaternion(Quaternion quat) = 0;
	virtual void startTracking(string id) = 0;
	virtual void stopTracking(string id) = 0;
};
