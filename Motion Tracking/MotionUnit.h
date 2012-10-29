#pragma once

#include "MoTingLib.h"
#include <string>
#include <vector>

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
	MotionUnit(const string& id);

	/// <summary>
	///	Copy constructor.
	/// </summary>
	MotionUnit(const MotionUnit& other);

	/// <summary>
	/// Finalizes an instance of the <see cref="MoTing::MotionUnit" /> class.
	/// </summary>
	virtual ~MotionUnit();

	/// <summary>
	/// Gets the id.
	/// </summary>
	/// <returns>MotionUnit identy respresents.</returns>
	const string& getId() const;

	/// <summary>
	/// Gets the orientation.
	/// </summary>
	/// <returns>Current absolute orientation as a quaternion.</returns>
	const Quaternion& getOrientation() const;

	/// <summary>
	/// Sets the id.
	/// </summary>
	/// <param name="newId">The new id.</param>
	void setId(const string& newId);

	/// <summary>
	/// Sets the orientation.
	/// </summary>
	/// <param name="newOrientation">The new orientation.</param>
	void setOrientation(const Quaternion& newOrientation);

private:
	string id;
	Quaternion orientation;
	MotionUnit& operator=(const MotionUnit& other);
};
