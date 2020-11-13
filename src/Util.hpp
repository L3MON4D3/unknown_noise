#include "FastNoise.h"
#include <functional>

namespace unknown_noise {
namespace util {

struct Noise {
	/**
	*
	* @param x_stretch Resolution eg. noise(res*x).
	*/
	/**
	 * @brief Create NoiseMods. Controls "Resolution", amplification and final
	 * noise.
	 *
	 * @param def_range Defined Range of Noise, eg size of amplification- and
	 *  res/pos-arrays.
	 * @param x_pos_fill Mapping of x-values 0 through def_range to actual
	 *  x-values in noise.
	 * @param res_fill Result-stretch function, calculate how much noise at x-coord
	 *   should be stretched.
	 * @param post_stretch_filter Input is stretched noise and x-Coord, output float.
	 * @param fn Instance of FastNoise.
	 */
	Noise(
	  const int def_range,
	  const std::function<float(int x)> x_pos_fill,
	  const std::function<float(int x)> res_fill,
	  const std::function<float(float noise, int x)> post_stretch_filter,
	  const FastNoise& fn
	);

	~Noise();

	/**
	* @brief Get Noise modified by this Noise(mod).
	*
	* @param x Coord of Noise.
	* @param y Values should differ from noise to noise so there aren't duplicate lines.
	*
	* @return Modified Noise.
	*/
	float at(const int x, const int y) const;

	int def_range;
	float *res_stretch,
	      *x_pos_scale;

	std::function<float(float noise, int x)> post_stretch_filter;

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
