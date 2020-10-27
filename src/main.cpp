#include <cstdlib>
#include <functional>

#include "FastNoise.h"

#include "UnknownNoise.hpp"

const std::function<float(int x)> const_mod {
	[](int x) {
		return 60;
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

	unknown_noise::make_picture({{0,0}, {100, 200}, 1, 10, 100, 40},
		fn, {0.1, 100, const_mod, no_filter}, "unknown_noise.png");
}
