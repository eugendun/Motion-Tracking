#pragma once

#include <vector>
#include <boost/math/quaternion.hpp>
#include <boost/random/uniform_01.hpp>
#include <boost/random/linear_congruential.hpp>

namespace MoTing
{
	typedef boost::math::quaternion<float> Quaternion;

	Quaternion _getRandomQuaternion() {
		boost::minstd_rand						intgen;
		boost::uniform_01<boost::minstd_rand>	gen(intgen);
		return Quaternion((float)gen(), (float)gen(), (float)gen(), (float)gen());
	}
}
