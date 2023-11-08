//
// Created by alexs on 11/8/2023.
//

#ifndef FIRELIGHT_OPEN_GL_DRIVER_HPP
#define FIRELIGHT_OPEN_GL_DRIVER_HPP

#include "driver.hpp"

namespace FL::Graphics {

class OpenGLDriver : public FL::Graphics::Driver {
public:
  void drawRectangle(int x, int y, int w, int h) override;
  void drawText(std::string text, int x, int y) override;
};

} // namespace FL::Graphics

#endif // FIRELIGHT_OPEN_GL_DRIVER_HPP
