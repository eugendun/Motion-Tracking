#include "Bone.h"

/// <summary>
/// Initializes a new instance of the <see cref="Bone" /> class.
/// </summary>
/// <param name="name">The name.</param>
Bone::Bone(string name)
	: name(name) {
	motionUnit = NULL;
	parent = NULL;
}

Bone::Bone(string name, MotionUnit& imu)
	: name(name),
	  motionUnit(&imu) {
	parent = NULL;
}

Bone::~Bone() {}

void Bone::setParent(Bone* bone) {
	parent = bone;
}

std::string Bone::getName() {
	return name;
}

/// <summary>
/// Gets the parent.
/// </summary>
/// <returns></returns>
Bone* Bone::getParent() {
	return parent;
}

/**
 *  if there is no bone in the list with this name, the end iterator
 *	will be returned.
 */
BoneList::iterator getBoneListIterator(string& name, BoneList& list) {
	BoneList::iterator it = list.begin();
	for (it; it != list.end(); it++) {
		if ((*it)->getName() == name) {
			return it;
		}
	}
	return list.end();
}

/**
 *  Each subordinate bone should be appear only once in the child list.
 */
 /// <summary>
/// Adds the child.
/// </summary>
/// <param name="bone">The bone.</param>
void Bone::addChild(Bone& bone) {
	BoneList::iterator it = getBoneListIterator(bone.getName(), childBones);
	if (it == childBones.end()) {
		if (bone.getParent()) {
			bone.getParent()->removeChildByName(bone.getName());
		}
		bone.setParent(this);
		Bone* pBone = &bone;
		childBones.push_back(pBone);
	}
}

 /// <summary>
/// Removes the name of the child by.
/// </summary>
/// <param name="name">The name.</param>
void Bone::removeChildByName(string& name) {
	BoneList::iterator it = getBoneListIterator(name, childBones);
	if (it != childBones.end()) {
		(*it)->setParent(NULL);
		childBones.erase(it);
	}
}

MoTing::Quaternion Bone::getRotation() {
	if (!motionUnit) {
		return Quaternion(0.0, 0.0, 0.0, 0.0);
	}

	if (!parent) {
		return motionUnit->getOrientation();
	}

	Quaternion parentRot = parent->getRotation();
	return parentRot * motionUnit->getOrientation() * boost::math::conj(parentRot);
}

void Bone::attachMotionUnit(MotionUnit& imu) {
	motionUnit = &imu;
}

void Bone::detachMotionUnit() {
	if (motionUnit) {
		motionUnit = NULL;
	}
}
