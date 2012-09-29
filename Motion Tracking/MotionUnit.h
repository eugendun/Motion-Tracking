#pragma once

#include <string>
#include <vector>
#include <boost/math/quaternion.hpp>

using namespace std;

namespace MoTing
{

class MotionUnit;

typedef vector<MotionUnit> MotionUnitList;
typedef boost::math::quaternion<float> Quaternion;

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
	string& getId();

	/// <summary>
	/// Gets the orientation.
	/// </summary>
	/// <returns>Current absolute orientation as a quaternion.</returns>
	Quaternion& getOrientation();

	/// <summary>
	/// Gets the relative orientation.
	/// </summary>
	/// <returns>Current relative orientation as a quaternion.</returns>
	Quaternion& getRelativeOrientation();

	/// <summary>
	/// Gets the parent.
	/// </summary>
	/// <returns>A Pointer to the superordinate MotionUnit. If no parent element is given, returns 0.</returns>
	MotionUnit* getParent();

	/// <summary>
	/// Gets all subordinate MotionUnits.
	/// </summary>
	/// <returns>MotionUnitList contains all subordinate MotionUnits.</returns>
	MotionUnitList& getChilds();

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

	/// <summary>
	/// Sets the parent.
	/// </summary>
	/// <param name="pNewParent">Pointer to the superordinate MotionUnit.</param>
	void setParent(MotionUnit* pNewParent);

	/// <summary>
	/// Adds the child.
	/// </summary>
	/// <param name="rNewChild">The subordinate MotionUnit.</param>
	void addChild(MotionUnit& rNewChild);

	/// <summary>
	/// Removes the subordinate MotionUnit by id.
	/// </summary>
	/// <param name="sChildId">The id of a MotionUnit that should be removed from subordinate MotionUnits.</param>
	void removeChildById(string sChildId);

private:
	/// <summary>
	/// Identifies the MotionUnit.
	/// </summary>
	string id;

	/// <summary>
	/// The current orientation of the MotionUnit.
	/// </summary>
	Quaternion orientation;

	/// <summary>
	/// Pointer to the superordinate MotionUnit.
	/// </summary>
	MotionUnit* parent;

	/// <summary>
	/// List of subordinated MotionUnits.
	/// </summary>
	MotionUnitList childs;
};
}
