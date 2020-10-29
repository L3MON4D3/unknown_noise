#include "Util.hpp"

namespace unknown_noise {
namespace util {


Noise::Noise(
  float x_stretch,
  int res_stretch_sz,
  const std::function<float(int x)> res_fill,
  const std::function<float(float noise, int x)> post_stretch_filter,
  const FastNoise& fn
)
	: x_stretch{ x_stretch },
	  res_stretch_sz{ res_stretch_sz },
	  res_stretch{ new float[res_stretch_sz] },
	  post_stretch_filter{ post_stretch_filter },
	  fn{ fn } { 
	
	for(int i{0}; i != res_stretch_sz; ++i)
		res_stretch[i] = res_fill(i);
}

float get_noise_modfd(Noise n, FastNoise fn, int x, int y) {
	return n.post_stretch_filter(n.res_stretch[x]*fn.GetNoise(n.x_stretch*x, y), x);
}

};
};
