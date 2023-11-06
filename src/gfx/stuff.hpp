//
// Created by alexs on 10/30/2023.
//

#ifndef BLUEMBER_STUFF_HPP
#define BLUEMBER_STUFF_HPP

#include "GL/glew.h"
#include <array>
#include <cstdio>
#include <cstdlib>
#include <cstring>
namespace Stuff {

class Thing {
public:
  std::array<float, 9> vertices = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f,
                                   0.0f,  0.0f,  0.5f, 0.0f};

  // compiler combines adjacent strings apparently
  const GLchar *fragmentShader = "#version 330 core\n"
                                 "out vec4 FragColor;\n"

                                 "void main()\n"
                                 "{\n"
                                 " FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                 "}\0";

  // compiler combines adjacent strings apparently
  const char *vertexShaderSource =
      "#version 330 core\n"
      "layout (location = 0) in vec3 aPos;\n"
      "void main()\n"
      "{\n"
      "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
      "}\0";

  GLuint vao;
  GLuint vbo;
  GLuint program;

  Thing() {

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(),
                 GL_STATIC_DRAW);

    auto err = glGetError();
    if (err != GL_NO_ERROR) {
      printf("GL ERROR: %d\n", err);
    }

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    err = glGetError();
    if (err != GL_NO_ERROR) {
      printf("GL ERROR: %d\n", err);
    }

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                          (void *)nullptr);
    glEnableVertexAttribArray(0);

    err = glGetError();
    if (err != GL_NO_ERROR) {
      printf("GL ERROR: %d\n", err);
    }

    //  glBindBuffer(GL_ARRAY_BUFFER, 0);
    //  glBindVertexArray(0);

    err = glGetError();
    if (err != GL_NO_ERROR) {
      printf("GL ERROR: %d\n", err);
    }

    auto frag = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(frag, 1, &fragmentShader, nullptr);
    glCompileShader(frag);

    GLint status;
    glGetShaderiv(frag, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE) {
      printf("Oh no, error: %d :(\n", status);
    }

    auto vert = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vert, 1, &vertexShaderSource, nullptr);
    glCompileShader(vert);

    status;
    glGetShaderiv(vert, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE) {
      printf("Oh no, error: %d :(\n", status);
      GLint logLength;
      glGetShaderiv(vert, GL_INFO_LOG_LENGTH, &logLength);

      char *str = static_cast<char *>(malloc(logLength + 1));
      memset(str, 'a', logLength);
      str[logLength] = '\0';
      glGetShaderInfoLog(vert, logLength, nullptr, str);

      printf("error: %s\n", str);
    }

    program = glCreateProgram();
    glAttachShader(program, frag);
    glAttachShader(program, vert);

    err = glGetError();
    if (err != GL_NO_ERROR) {
      printf("GL ERROR: %d\n", err);
    }

    glLinkProgram(program);
    //  glDetachShader(program, vert);
    //  glDetachShader(program, frag);

    err = glGetError();
    if (err != GL_NO_ERROR) {
      printf("GL ERROR: %d\n", err);
    }

    glDeleteShader(vert);
    glDeleteShader(frag);

    err = glGetError();
    if (err != GL_NO_ERROR) {
      printf("GL ERROR: %d\n", err);
    }
  }

  void drawRect(int x, int y, int w, int h) {
    glUseProgram(program);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    auto err = glGetError();
    if (err != GL_NO_ERROR) {
      printf("GL ERROR: %d\n", err);
    }
  }
};

} // namespace Stuff

#endif // BLUEMBER_STUFF_HPP
