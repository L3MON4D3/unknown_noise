#include "FastNoise.h"
#include <functional>

namespace unknown_noise {
namespace util {

struct Noise {
	/**
	* @brief Create NoiseMods. Controls "Resolution", amplification and final
	* noise.
	*
	* @param x_stretch Resolution eg. noise(res*x).
	* @param res_fill Result-stretch function, calculate how much noise at x-coord
	*   should be stretched.
	* @param post_stretch_filter Input is stretched noise and x-Coord, output float.
	*/
	Noise(
	  const float x_stretch,
	  const int res_stretch_sz,
	  const std::function<float(int x)> res_fill,
	  const std::function<float(float noise, int x)> post_stretch_filter,
	  const FastNoise& fn
	);

	/**
	* @brief Get Noise modified by this Noise(mod).
	*
	* @param x Coord of Noise.
	* @param y Values should differ from noise to noise so there aren't duplicate lines.
	*
	* @return Modified Noise.
	*/
	float at(int x, int y) const;

	const int res_stretch_sz;
	const float x_stretch;
	float *res_stretch;

	const std::function<float(float noise, int x)> post_stretch_filter;

	FastNoise fn;
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

};
};
