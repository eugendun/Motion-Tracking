#pragma once
#include <vector>
#include "MotionUnit.h"

using std::vector;
using namespace MoTing;

/// <summary>
/// Controller interface. 
/// </summary>
class Controller
{
	/// <summary>
	/// Gets MotionUnits.
	/// </summary>
	/// <returns>MotionUnitList</returns>
	virtual MotionUnitList getMotionUnits() = 0;

	/// <summary>
	/// Starts tracking.
	/// </summary>
	/// <param name="mUnit">MotionUnit that should be tracked.</param>
	virtual void startTracking(MotionUnit& mUnit) = 0;

	/// <summary>
	/// Stops tracking.
	/// </summary>
	/// <param name="mUnit">MotionUnit that should be stoped to track.</param>
	virtual void stopTracking(MotionUnit& mUnit) = 0;

	/// <summary>
	/// Tares the specified MotionUnit.
	/// </summary>
	/// <param name="mUnit">MotionUnit that should be tared.</param>
	virtual void tare(MotionUnit& mUnit) = 0;
};
