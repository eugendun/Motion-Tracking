#pragma once

#include <MoTingLib.h>
#include <Bone.h>
#include <boost/test/included/unit_test.hpp>

class Test_Bone
{
public:
	Test_Bone()
		: m1("m1"),
		  m2("m2"),
		  m3("m3"),
		  b1("b1"),
		  b2("b2", m2),
		  b3("b3", m3) {
		m1.setOrientation(_getRandomQuaternion());
		m2.setOrientation(_getRandomQuaternion());
		m3.setOrientation(_getRandomQuaternion());
	}
	~Test_Bone() {}

	/**
	 *  Tests the Bone constructors.
	 */
	void test_Constructors() {
		BOOST_CHECK(b1.getName() == "b1");
		BOOST_CHECK(!b1.getParent());
		BOOST_CHECK(b1.getRotation() == Quaternion(0.0, 0.0, 0.0, 0.0));

		BOOST_CHECK(b2.getName() == "b2");
		BOOST_CHECK(b2.getRotation() == m2.getOrientation());
	}

	/**
	 *  Tests the Bones attachment and detachment of a MotionUnit. A Bone should have the
	 *	same orientation as the attached MotionUnit. When the MotionUnit will be detached the
	 *	orientation of the correlated Bone should not be updated anymore if the orientation 
	 *	of MotionUnit will be changed.
	 */
	void test_AttachDetach() {
		b1.attachMotionUnit(m1);
		BOOST_CHECK(b1.getRotation() == m1.getOrientation());

		b1.detachMotionUnit();
		m1.setOrientation(_getRandomQuaternion());
		BOOST_CHECK(b1.getRotation() != m1.getOrientation());

		b1.attachMotionUnit(m1);
		BOOST_CHECK(b1.getRotation() == m1.getOrientation());
	}

	/**
	 *  Tests the Bones add and remove function of a subordinate Bone. The orientation of a 
	 *	subordinate Bone will be calculated relative to the parent Bone. If the MotionUnit
	 *	orientations of the correlated Bones b1, b2 are rot1, rot2 then the orientation of
	 *	b2 will be calculated as fallows: b2.rot = rot1 * rot2 * conj(rot1)
	 */
	void test_AddRemoveChild() {
		Quaternion	rot2 = m1.getOrientation() * m2.getOrientation() * conj(m1.getOrientation());
		b1.addChild(b2);
		BOOST_CHECK(b2.getParent());
		BOOST_CHECK(b2.getRotation() == rot2);

		b1.removeChildByName(b2.getName());
		BOOST_CHECK(!b2.getParent());
		BOOST_CHECK(b2.getRotation() == m2.getOrientation());

		Quaternion	rot3 = rot2 * m3.getOrientation() * conj(rot2);
		b1.addChild(b2);
		b2.addChild(b3);
		BOOST_CHECK(b3.getParent());
		BOOST_CHECK(b3.getRotation() == rot3);

		rot3 = m2.getOrientation() * m3.getOrientation() * conj(m2.getOrientation());
		b1.removeChildByName(b2.getName());
		BOOST_CHECK(!b2.getParent());
		BOOST_CHECK(b2.getRotation() == m2.getOrientation());
		BOOST_CHECK(b3.getParent());
		BOOST_CHECK(b3.getRotation() == rot3);

		b2.removeChildByName(b3.getName());
		BOOST_CHECK(!b3.getParent());
		BOOST_CHECK(b3.getRotation() == m3.getOrientation());
	}

private:
	Bone b1, b2, b3;
	MotionUnit m1, m2, m3;
};
