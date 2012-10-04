#pragma once

#include "MoTingLib.h"
#include <string>

using std::string;
using MoTing::Quaternion;

class MotionUnit;

typedef std::vector<MotionUnit*> MotionUnitList;

/// <summary>
/// MotionUnit represent single inertial measurement unit.
/// </summary>
class MotionUnit
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="MoTing::MotionUnit" /> class.
	/// </summary>
	/// <param name="id">The id.</param>
	MotionUnit(string id);

	/// <summary>
	/// Finalizes an instance of the <see cref="MoTing::MotionUnit" /> class.
	/// </summary>
	virtual ~MotionUnit(void);

	/// <summary>
	/// Gets the id.
	/// </summary>
	/// <returns>MotionUnit identy respresents.</returns>
	string getId();

	/// <summary>
	/// Gets the orientation.
	/// </summary>
	/// <returns>Current absolute orientation as a quaternion.</returns>
	Quaternion getOrientation();

	/// <summary>
	/// Sets the id.
	/// </summary>
	/// <param name="newId">The new id.</param>
	void setId(string& newId);

	/// <summary>
	/// Sets the orientation.
	/// </summary>
	/// <param name="newOrientation">The new orientation.</param>
	void setOrientation(Quaternion& newOrientation);

private:
	string id;
	Quaternion orientation;
};
