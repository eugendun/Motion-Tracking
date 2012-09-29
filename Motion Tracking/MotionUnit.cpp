#include "MotionUnit.h"

using namespace MoTing;

MotionUnit::MotionUnit(string id) {
	setId(id);
}

MotionUnit::~MotionUnit(void) {}


string& MotionUnit::getId() {
	return id;
}

Quaternion& MotionUnit::getOrientation() {
	return orientation;
}

Quaternion& MotionUnit::getRelativeOrientation() {
	if (!parent) {
		return orientation;
	}

	return parent->getRelativeOrientation() * orientation;
}


MotionUnit* MotionUnit::getParent() {
	return parent;
}

MotionUnitList& MotionUnit::getChilds() {
	return childs;
}

void MotionUnit::setId(string& newId) {
	id = newId;
}

void MotionUnit::setOrientation(Quaternion& newOrientation) {
	orientation = newOrientation;
}

void MotionUnit::setParent(MotionUnit* pNewParent) {
	parent = pNewParent;
}

void MotionUnit::addChild(MotionUnit& rNewChild) {
	childs.push_back(rNewChild);
}

MotionUnitList::iterator* getMotionListIterator(MotionUnitList& motionUnitList, string& sChildId) {
	MotionUnitList::iterator it = motionUnitList.begin();
	for (it; it != motionUnitList.end(); it++) {
		if (it->getId() == sChildId) {
			return &it;
		}
	}

	return &it;
}

void MotionUnit::removeChildById(string sChildId) {
	//MotionUnitList
}
