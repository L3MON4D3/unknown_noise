#include "Util.hpp"
#include <cairomm/context.h>
#include <cairomm/refptr.h>
#include <cairomm/surface.h>

namespace unknown_noise {

/**
 * @brief Generate new Picture.
 *
 * @param dims Info on various dimensions, more in util.
 * @param n Noise modfications, more in util.
 * @param name Filename of Picture.
 */
void make_picture(
  const util::Dimensions dims,
  const util::Noise& n,
  const std::string name
);
};
