#include <iostream>
#include <memory>
#include <string>
#define _USE_MATH_DEFINES
#include <cmath>
#include <cstdlib>
#include <functional>

#include "FastNoise.h"

#include "UnknownNoise.hpp"

//Bell-shaped function.
float witch(float x, float a) {
	return (8*std::pow(a, 3))/(std::pow(x, 2)+ 4*std::pow(a, 2));
}

float mod_func(float x) {
	if (x < 400)
		return witch(x*(32.0f/800)-16, 2);
	else if (x < 800)
		return witch(0, 2);
	else
		return witch(x*(32.0f/800)-32, 2);
}

const std::function<float(int x)> simplex_x_pos {
	[](int x) {
		return .3;
	}
};

const std::function<float(int x)> simplex_mod {
	[](int x) {
		return mod_func(x)*15;
	}
};

const std::function<float(float noise, int x)> simplex_filter {
	[](float noise, int x) {
		return noise - mod_func(x)*15;
	}
};

const std::function<float(int x)> perlin_x_pos {
	[](int x) {
		return 6;
	}
};

const std::function<float(int x)> perlin_mod {
	[](int x) {
		return mod_func(x)*1;
	}
};

const std::function<float(float noise, int x)> perlin_filter {
	[](float noise, int x) {
		return noise-mod_func(x)*1;
	}
};

int main(int argc, char** argv) {
	FastNoise fn, fn2;
	fn.SetNoiseType(FastNoise::SimplexFractal);
	fn2.SetNoiseType(FastNoise::Perlin);

	srand(time(0));
	fn.SetSeed(std::rand());
	fn2.SetSeed(std::rand());

	using unknown_noise::util::Noise;
	std::vector<std::unique_ptr<Noise>> vec;
	vec.push_back(std::unique_ptr<Noise>{new Noise{1200, simplex_x_pos, simplex_mod, simplex_filter, fn}});
	//res_stretch_sz should be equal to hor_count.
	unknown_noise::make_picture(
		{{40, 225}, {680, 1200}, .5, 8, 1200, 100}, vec, "unknown_noise.png");
}
