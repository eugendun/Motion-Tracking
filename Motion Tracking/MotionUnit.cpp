#include "MotionUnit.h"

MotionUnit::MotionUnit(const string& id)
	: id(id),
	  orientation(Quaternion(0.0, 0.0, 0.0, 0.0)) {}

MotionUnit::~MotionUnit(void) {}

MotionUnit::MotionUnit(const MotionUnit& other)
	: id(other.id),
	  orientation(other.orientation) {}

const string& MotionUnit::getId() const {
	return id;
}

const Quaternion& MotionUnit::getOrientation() const {
	return orientation;
}

void MotionUnit::setId(const string& newId) {
	id = newId;
}

void MotionUnit::setOrientation(const Quaternion& newOrientation) {
	orientation = newOrientation;
}
