#include "MotionUnit.h"

using namespace MoTing;

MotionUnit::MotionUnit(string id)
	: id(id),
	  parent(0) {}

MotionUnit::~MotionUnit(void) {}


string MotionUnit::getId() {
	return id;
}

Quaternion MotionUnit::getOrientation() {
	return orientation;
}

Quaternion MotionUnit::getRelativeOrientation() {
	if (!parent) {
		return orientation;
	}

	return parent->getRelativeOrientation() * orientation;
}


MotionUnit* MotionUnit::getParent() {
	return parent ? parent : 0;
}

MotionUnitList MotionUnit::getChilds() {
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

// 1. set this as parent of rNewChild therefore it has to checked that rNewChild is not listed in list of old parent.
void MotionUnit::addChild(MotionUnit& rNewChild) {
	if (rNewChild.getParent()) {
		rNewChild.getParent()->removeChildById(rNewChild.getId());
	}
	rNewChild.setParent(this);
	this->childs.push_back(rNewChild);
}

MotionUnitList::iterator getMotionListIterator(MotionUnitList& motionUnitList, string& sChildId) {
	MotionUnitList::iterator it = motionUnitList.begin();
	for (it; it != motionUnitList.end(); it++) {
		if (it->getId() == sChildId) {
			return it;
		}
	}
	return motionUnitList.end();
}

void MotionUnit::removeChildById(string sChildId) {
	MotionUnitList::iterator it = getMotionListIterator(childs, sChildId);
	if (it != childs.end()) {
		it->setParent(0);
		childs.erase(it);
	}
}
