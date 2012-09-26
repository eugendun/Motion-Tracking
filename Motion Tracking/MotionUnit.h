#pragma once

#include <string>
#include <vector>
#include <boost/math/quaternion.hpp>

using std::string;
using std::vector;
using boost::math::quaternion;

class MotionUnit
{
public:
	MotionUnit(string id);
	virtual ~MotionUnit(void);

	string& getId();
	quaternion<float>& getOrientation();
	quaternion<float>& getRelativeOrientation();
	MotionUnit* getParent();
	vector<MotionUnit&>& getChilds();

	void setId(string& id);
	void setOrientation(quaternion<float>& newOrientation);
	void setParent(MotionUnit* mUnit);
	void addChild(MotionUnit& mUnit);

private:
	string id;
	quaternion<float> orientation;
	MotionUnit* parent;
	vector<MotionUnit&> childs;
};

