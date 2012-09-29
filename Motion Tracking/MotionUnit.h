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

class MotionUnit
{
public:
	MotionUnit(string id);
	virtual ~MotionUnit(void);

	string& getId();
	Quaternion& getOrientation();
	Quaternion& getRelativeOrientation();
	MotionUnit* getParent();
	MotionUnitList& getChilds();

	void setId(string& newId);
	void setOrientation(Quaternion& newOrientation);
	void setParent(MotionUnit* pNewParent);
	void addChild(MotionUnit& rNewChild);
	void removeChildById(string sChildId);

private:
	string id;
	Quaternion orientation;
	MotionUnit* parent;
	MotionUnitList childs;
};
}
