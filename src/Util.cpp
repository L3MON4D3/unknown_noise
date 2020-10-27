#include "Util.hpp"

namespace unknown_noise {
namespace util {


NoiseMods::NoiseMods(
  float x_stretch,
  int res_stretch_sz,
  const std::function<float(int x)> res_fill,
  const std::function<float(float noise, int x)> post_stretch_filter
)
	: x_stretch{ x_stretch },
	  res_stretch_sz{ res_stretch_sz },
	  res_stretch{ new float[res_stretch_sz] },
	  post_stretch_filter{ post_stretch_filter } { 
	
	for(int i{0}; i != res_stretch_sz; ++i)
		res_stretch[i] = res_fill(i);
}

float get_noise_modfd(NoiseMods nm, FastNoise fn, int x) {
	return nm.post_stretch_filter(nm.res_stretch[x]*fn.GetNoise(nm.x_stretch*x, 0), x);
}

};
};
