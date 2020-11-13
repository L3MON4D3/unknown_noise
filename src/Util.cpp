#include "Util.hpp"
#include <iostream>

namespace unknown_noise {
namespace util {


Noise::Noise(
  const int def_range,
  const std::function<float(int x)> x_pos_fill,
  const std::function<float(int x)> res_fill,
  const std::function<float(float noise, int x)> post_stretch_filter,
  const FastNoise& fn
)
	: def_range{ def_range },
	  x_pos_scale{ new float[def_range] },
	  res_stretch{ new float[def_range] },
	  post_stretch_filter{ post_stretch_filter },
	  fn{ fn } { 

	for(int i{0}; i != def_range; ++i)
		res_stretch[i] = res_fill(i);

	//Map actual position of x(x_pos_scale[x]) to range 0-def_range.
	x_pos_scale[0] = x_pos_fill(0);
	for(int i{1}; i < def_range; ++i)
		x_pos_scale[i] = x_pos_fill(i) + x_pos_scale[i-1];
}

Noise::~Noise() {
	delete[] res_stretch, delete[] x_pos_scale;
}

float Noise::at(const int x, const int y) const {
	return post_stretch_filter(res_stretch[x]*fn.GetNoise(x_pos_scale[x], y), x);
}

};
};
