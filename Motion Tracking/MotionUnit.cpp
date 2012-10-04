#include "MotionUnit.h"

using namespace MoTing;

MotionUnit::MotionUnit(string id)
	: id(id) {}

MotionUnit::~MotionUnit(void) {}


string MotionUnit::getId() {
	return id;
}

Quaternion MotionUnit::getOrientation() {
	return orientation;
}

void MotionUnit::setId(string& newId) {
	id = newId;
}

void MotionUnit::setOrientation(Quaternion& newOrientation) {
	orientation = newOrientation;
}
