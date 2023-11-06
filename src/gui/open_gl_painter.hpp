//
// Created by alexs on 10/31/2023.
//

#ifndef BLUEMBER_OPEN_GL_PAINTER_HPP
#define BLUEMBER_OPEN_GL_PAINTER_HPP

#include "GL/glew.h"
#include "character.hpp"
#include <array>
#include <freetype/freetype.h>
#include <ft2build.h>
#include <string>
#include <unordered_map>
namespace FL::GUI {

class OpenGLPainter {
public:
  OpenGLPainter(int w, int h);
  ~OpenGLPainter();
  void drawRectangle(int x, int y, int w, int h);
  void drawTexture(unsigned tex, int x, int y, unsigned w, unsigned h);
  void drawText(const std::string &text, int x, int y);
  int viewportWidth, viewportHeight = 0;

private:
  FT_Library fontLib;
  FT_Face fontFace;
  GLuint fontTex;
  GLuint vao;
  GLuint vbo;
  GLuint program;

  GLuint texVao;
  GLuint texVbo;
  [[nodiscard]] std::array<float, 8> calculateVertexArray(int x, int y, int w,
                                                          int h) const;
  [[nodiscard]] std::array<float, 16>
  calculateTexVertexArray(int x, int y, int w, int h) const;
  std::unordered_map<char, Character> characters;
};

} // namespace FL::GUI

#endif // BLUEMBER_OPEN_GL_PAINTER_HPP
