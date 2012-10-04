#pragma once

#include "MotionUnit.h"
#include <string>
#include <vector>

using namespace MoTing;

class Bone;

typedef vector<Bone*> BoneList;

/// <summary>
/// Bone structure represent a skeleton.
/// </summary>
class Bone
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="Bone" /> class.
	/// </summary>
	/// <param name="name">The name of the bone.</param>
	Bone(string name);

	/// <summary>
	/// Initializes a new instance of the <see cref="Bone" /> class.
	/// </summary>
	/// <param name="name">The name of the bone.</param>
	/// <param name="imu">Attached MotionUnit</param>
	Bone(string name, MotionUnit& imu);

	/// <summary>
	/// Finalizes an instance of the <see cref="Bone" /> class.
	/// </summary>
	virtual ~Bone();

	/// <summary>
	/// Gets the name.
	/// </summary>
	/// <returns></returns>
	string getName();

	/// <summary>
	/// </summary>
	/// <returns></returns>
	Bone* getParent();

	/// <summary>
	/// Gets the rotation.
	/// </summary>
	/// <returns></returns>
	Quaternion getRotation();
	
	/// <summary>
	/// Adds a subordinate bone.
	/// </summary>
	void addChild(Bone& bone);

	/// <summary>
	/// Removes a subordinate bone given by name.
	/// </summary>
	void removeChildByName(string& name);

	/// <summary>
	/// Attaches a MotionUnit. 
	/// </summary>
	void attachMotionUnit(MotionUnit& imu);

	/// <summary>
	/// Detaches the actual MotionUnit.
	/// </summary>
	void detachMotionUnit();

private:
	string name;
	MotionUnit* motionUnit;
	Bone* parent;
	BoneList childBones;

	void setParent(Bone* bone);
};

