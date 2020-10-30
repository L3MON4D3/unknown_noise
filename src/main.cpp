#include <string>
#define _USE_MATH_DEFINES
#include <cmath>
#include <cstdlib>
#include <functional>

#include "FastNoise.h"

#include "UnknownNoise.hpp"

//Bell-shaped function.
const std::function<float(float x)> witch {
	[](float x) {
		float actual_x {x*(50.0f/600)};
		float a {1};
		return (8*std::pow(a, 3))/(std::pow(actual_x-25, 2)+ 4*std::pow(a, 2));
	}
};

const std::function<float(int x)> simplex_mod {
	[](int x) {
		return witch(x)*10;
	}
};

const std::function<float(float noise, int x)> simplex_filter {
	[](float noise, int x) {
		return noise - witch(x)*10;
	}
};

int main(int argc, char** argv) {
	FastNoise fn;
	fn.SetNoiseType(FastNoise::Simplex);

	srand(time(0));
	fn.SetSeed(std::rand());

	//res_stretch_sz should be equal to hor_count.
	unknown_noise::make_picture({{190, 225}, {680, 1200}, .5, 8, 600, 50},
		{{1, 600, simplex_mod, simplex_filter, fn}}, "unknown_noise.png");
}
