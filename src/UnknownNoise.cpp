#include "UnknownNoise.hpp"
#include <cairomm/context.h>
#include <cairomm/path.h>
#include <cairomm/refptr.h>

#include <iostream>

namespace unknown_noise {

//anonymous namespace to contain 'private' functions.
namespace {

void draw_line(
  const float start_y,
  const util::Dimensions dims,
  const util::Noise& n,
  Cairo::RefPtr<Cairo::Context> ctx
) {
	//save current x_pos seperately to avoid multiplication.
	float x_pos { dims.start[0] };

	//First move is seperate as there is no point to move from.
	ctx->begin_new_path();
	ctx->move_to(x_pos, start_y+n.at(0, start_y*100));
	x_pos+=dims.hor_space;

	for(int i{1}; i <= dims.hor_count; ++i, x_pos+=dims.hor_space) {
		//Get noise at position i and subtract/add it to y-coord of point.
		//start_y*100 because else lines look very similar.
		float noise {n.at(i, start_y*100)};
		ctx->line_to(x_pos, start_y+noise);
	}
	//Copy path bcs fill needs to be done first, else blurry edges.
	Cairo::Path *p = ctx->copy_path();
	ctx->line_to(x_pos, start_y+1);
	ctx->line_to(dims.start[0], start_y+1);
	ctx->close_path();

	ctx->set_source_rgb(0, 0, 0);
	ctx->fill();

	//load Path to stroke.
	ctx->append_path(*p);
	ctx->set_source_rgb(1, 1, 1);
	ctx->stroke();
}

};

void make_picture(
  const util::Dimensions dims,
  const util::Noise& nm,
  const std::string name
) {
	auto surface =
		Cairo::ImageSurface::create(Cairo::FORMAT_RGB24, dims.size[0], dims.size[1]);
	auto cr = Cairo::Context::create(surface);

	float y_pos {dims.start[1]};
	for(int i{0}; i != dims.ver_count; ++i, y_pos+=dims.ver_space)
		draw_line(y_pos, dims, nm, cr);
	surface->write_to_png(name);
}

};
