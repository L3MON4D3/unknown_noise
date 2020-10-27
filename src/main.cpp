#include <cstdlib>
#include <functional>

#include "FastNoise.h"

#include "UnknownNoise.hpp"

const std::function<float(int x)> const_mod {
	[](int x) {
		return 5;
	}
};

const std::function<float(float noise, int x)> no_filter {
	[](float noise, int x) {
		return noise;
	}
};

int main(int argc, char** argv) {
	FastNoise fn;
	fn.SetNoiseType(FastNoise::Perlin);
	fn.SetSeed(std::rand());

	//res_stretch_sz should be equal to hor_count.
	unknown_noise::make_picture({{0,0}, {1000, 1500}, 1, 100, 1000, 40},
		fn, {5, 1000, const_mod, no_filter}, "unknown_noise.png");
}
