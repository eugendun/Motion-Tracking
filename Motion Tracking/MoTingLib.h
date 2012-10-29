#pragma once

#include <boost/math/quaternion.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_real.hpp>
#include <boost/random/variate_generator.hpp>
#include <ctime>

namespace MoTing
{
typedef boost::math::quaternion<float> Quaternion;

class QuatGenerator
{
public:
	QuatGenerator()
		: gen(boost::mt19937(static_cast<unsigned int>(std::time(0)))) {};

	~QuatGenerator() {};

	Quaternion generate() {
		boost::uniform_real<> uni_dist(0,1);
		boost::variate_generator<boost::mt19937&, boost::uniform_real<>> uni_gen(gen, uni_dist);
		return Quaternion(static_cast<float>(uni_gen()), static_cast<float>(uni_gen()), static_cast<float>(uni_gen()),
						  static_cast<float>(uni_gen()));
	};

private:
	boost::mt19937 gen;

	QuatGenerator(const QuatGenerator& other);
	QuatGenerator& operator=(const QuatGenerator& other);
};
}
