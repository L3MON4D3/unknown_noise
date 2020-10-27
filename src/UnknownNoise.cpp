#include "UnknownNoise.hpp"

namespace unknown_noise {

void make_picture(
  const util::Dimensions dims,
  const FastNoise& fn,
  const util::NoiseMods& nm,
  const std::string name
) {
	auto surface =
		Cairo::ImageSurface::create(Cairo::FORMAT_RGB24, dims.size[0], dims.size[1]);
	auto cr = Cairo::Context::create(surface);

	cr->set_source_rgb(1, 0, 0);
	cr->paint();
	surface->write_to_png(name);
}

};
