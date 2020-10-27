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

struct Dimensions {
	//Start Position (x|y).
	float start[2],
	      //Size of Picture (x|y).
	      size[2],
	      //Space between two points on one line.
	      hor_space,
		  //Space between two lines.
	      ver_space;
	//Number of points for each line.
	int hor_count,
		//Number of Lines.
		ver_count;
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
