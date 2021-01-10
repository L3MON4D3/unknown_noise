#include "UnknownNoise.hpp"

#include <cairomm/context.h>
#include <cairomm/path.h>
#include <cairomm/refptr.h>

#include <algorithm>
#include <iostream>
#include <functional>


namespace unknown_noise {

//anonymous namespace to contain 'private' functions.
namespace {

void draw_line(
  const float start_y,
  const util::Dimensions dims,
  std::vector<util::Noise>& n,
  Cairo::RefPtr<Cairo::Context> ctx
) {
	//save current x_pos seperately to avoid multiplication.
	float x_pos { dims.start[0] };
	float y { start_y*1000 };
	int x {0};

	//First move is seperate as there is no point to move from.
	ctx->begin_new_path();
	float noise {start_y};

	const std::function<void(const util::Noise& n)> add_noise {
		[&noise, y, &x](const util::Noise& n) {
			noise+=n.at(x, y);
		}
	};

	std::for_each(n.begin(), n.end(), add_noise);
	ctx->move_to(x_pos, noise);
	x_pos+=dims.hor_space;

	for(; x <= dims.hor_count; ++x, x_pos+=dims.hor_space) {
		//Get noise at position i and subtract/add it to y-coord of point.
		//start_y*100 because else lines look very similar.
		noise = start_y;
		std::for_each(n.begin(), n.end(), add_noise);
		ctx->line_to(x_pos, noise);
	}
	//Copy path bcs fill needs to be done first, else blurry edges.
	Cairo::Path *p = ctx->copy_path();
	//fill Box beneath Path, overshadow lines behind.
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
  std::vector<util::Noise>& n,
  const std::string name
) {
	auto surface =
		Cairo::ImageSurface::create(Cairo::FORMAT_RGB24, dims.size[0], dims.size[1]);
	auto cr = Cairo::Context::create(surface);

	float y_pos {dims.start[1]};
	for(int i{0}; i != dims.ver_count; ++i, y_pos+=dims.ver_space)
		draw_line(y_pos, dims, n, cr);
	surface->write_to_png(name);
}

};
