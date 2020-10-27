#include "FastNoise.h"
#include <functional>

namespace unknown_noise {
namespace util {

struct NoiseMods {
	/**
	* @brief Create NoiseMods. Controls "Resolution", amplification and final
	* noise.
	*
	* @param x_stretch Resolution eg. noise(res*x).
	* @param res_fill Result-stretch function, calculate how much noise at x-coord
	*   should be stretched.
	* @param post_stretch_filter Input is stretched noise and x-Coord, output float.
	*/
	NoiseMods(
	  float x_stretch,
	  int res_stretch_sz,
	  const std::function<float(int x)> res_fill,
	  const std::function<float(float noise, int x)> post_stretch_filter
	);

	int res_stretch_sz;
	float x_stretch,
	      *res_stretch;

	const std::function<float(float noise, int x)> post_stretch_filter;
};

/**
* @brief Get Noise modified by nm.
*
* @param nm NoiseMods.
* @param fn FastNoise.
* @param x Coord of Noise.
*
* @return Modified Noise, possible modifications see NoiseMods.
*/
float get_noise_modfd(NoiseMods nm, FastNoise fn, int x);

};
};
