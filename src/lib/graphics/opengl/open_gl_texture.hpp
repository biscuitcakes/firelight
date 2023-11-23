//
// Created by alexs on 11/17/2023.
//

#ifndef FIRELIGHT_OPEN_GL_TEXTURE_HPP
#define FIRELIGHT_OPEN_GL_TEXTURE_HPP

#include "../texture.hpp"
#include <GL/glew.h>

namespace FL::Graphics {

class OpenGLTexture : public Texture {
public:
  void resize(int w, int h) override;

  GLuint texId = -1;

private:
  int width = 0;
  int height = 0;
};

} // namespace FL::Graphics

#endif // FIRELIGHT_OPEN_GL_TEXTURE_HPP
