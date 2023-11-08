//
// Created by alexs on 10/17/2023.
//

#include "video.hpp"
#include "../graphics/shaders.hpp"
#include "../includes/spdlog/spdlog.h"
#include <SDL2/SDL_video.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>

const GLchar *fragmentShader2 =
    "#version 410\n"
    "//uniform vec2 OutputSize;\n"
    "//uniform vec2 TextureSize;\n"
    "//uniform vec2 InputSize;\n"
    "uniform sampler2D Texture;\n"

    "in vec2 fragTexCoord;\n"

    "out vec4 FragColor;\n"

    "void main() {\n"
    "vec4 c = texture(Texture, fragTexCoord);\n"
    //"FragColor = vec4(1-c.x, 1-c.y, 1-c.z, c.a);\n"
    "FragColor = c;\n"
    "}\0";

const GLchar *fragmentShader = "#version 410\n"
                               "//uniform vec2 OutputSize;\n"
                               "//uniform vec2 TextureSize;\n"
                               "//uniform vec2 InputSize;\n"
                               "uniform sampler2D Texture;\n"

                               "in vec2 fragTexCoord;\n"

                               "out vec4 FragColor;\n"

                               "void main() {\n"
                               "vec4 c = texture(Texture, fragTexCoord);\n"
                               "FragColor = c;\n"
                               "//FragColor = vec4(fragTexCoord.xy, 0, 1.0);\n"
                               "}\0";

// compiler combines adjacent strings apparently
const GLchar *vertexShader = "#version 410\n"
                             "layout(location = 0) in vec2 vert;\n"
                             "layout(location = 1) in vec2 vertTexCoord;\n"

                             "out vec2 fragTexCoord;\n"

                             "void main() {\n"
                             "fragTexCoord = vertTexCoord;\n"
                             "gl_Position = vec4(vert, 0.0, 1.0);\n"
                             "}\0";

namespace libretro {
static GLuint fboId = 0;

void Video::recalcVertexArray() {
  if (this->gameGeometry == nullptr || this->displayMode == STRETCH) {
    this->vertices = {-1.0, -1.0, 0, 1.0, 1.0, -1.0, 1.0, 1.0,
                      -1.0, 1.0,  0, 0,   1.0, 1.0,  1.0, 0};
  } else if (this->displayMode == ORIGINAL) {
    auto geo = *this->gameGeometry;
    auto w = geo.base_width; // Can multiply here to do what I guess is integer
                             // scaling?
    auto h = geo.base_height;

    this->vertices = {
        -(w / float(windowWidth)), -(h / float(windowHeight)), 0,   1.0,
        (w / float(windowWidth)),  -(h / float(windowHeight)), 1.0, 1.0,
        -(w / float(windowWidth)), (h / float(windowHeight)),  0,   0,
        (w / float(windowWidth)),  (h / float(windowHeight)),  1.0, 0};
  } else if (this->displayMode == ASPECT_RATIO) {
    auto geo = *this->gameGeometry;
    auto aspectRatio = geo.aspect_ratio;

    auto calculatedAspectRatio = float(geo.base_width) / float(geo.base_height);

    if (calculatedAspectRatio < aspectRatio) {
      spdlog::info("Calculated aspect ratio {} is different than provided "
                   "aspect ratio {}; using calculated",
                   calculatedAspectRatio, aspectRatio);
      aspectRatio = calculatedAspectRatio;
    }

    auto desiredHeight = windowHeight;
    auto desiredWidth = windowHeight * aspectRatio;

    if (desiredWidth > windowWidth) {
      desiredWidth = windowWidth;
      desiredHeight = desiredWidth / aspectRatio;
    }

    this->vertices = {-(desiredWidth / float(windowWidth)),
                      -(desiredHeight / float(windowHeight)),
                      0,
                      1.0,
                      (desiredWidth / float(windowWidth)),
                      -(desiredHeight / float(windowHeight)),
                      1.0,
                      1.0,
                      -(desiredWidth / float(windowWidth)),
                      (desiredHeight / float(windowHeight)),
                      0,
                      0,
                      (desiredWidth / float(windowWidth)),
                      (desiredHeight / float(windowHeight)),
                      1.0,
                      0};
  }

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(),
               GL_STATIC_DRAW);
  auto err = glGetError();
  if (err != GL_NO_ERROR) {
    printf("GL ERROR: %d\n", err);
  }

  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Video::Video() {
  printf("OpenGL version: %s\n", glGetString(GL_VERSION));

  glGenBuffers(1, &intermediateVbo);
  glBindBuffer(GL_ARRAY_BUFFER, intermediateVbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(fullScreenVertices),
               fullScreenVertices.data(), GL_STATIC_DRAW);
  auto err = glGetError();
  if (err != GL_NO_ERROR) {
    printf("GL ERROR: %d\n", err);
  }

  glGenVertexArrays(1, &intermediateVao);
  glBindVertexArray(intermediateVao);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 2, GL_FLOAT, false, 4 * 4, nullptr);

  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 2, GL_FLOAT, false, 4 * 4,
                        (void *)(2 * sizeof(float)));

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(),
               GL_STATIC_DRAW);
  err = glGetError();
  if (err != GL_NO_ERROR) {
    printf("GL ERROR: %d\n", err);
  }

  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 2, GL_FLOAT, false, 4 * 4, nullptr);

  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 2, GL_FLOAT, false, 4 * 4,
                        (void *)(2 * sizeof(float)));

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

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

  err = glGetError();
  if (err != GL_NO_ERROR) {
    printf("GL ERROR: %d\n", err);
  }

  auto frag2 = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(frag2, 1, &fragmentShader2, nullptr);
  glCompileShader(frag2);

  auto vert = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vert, 1, &vertexShader, nullptr);
  glCompileShader(vert);

  GLint status2;

  glGetShaderiv(vert, GL_COMPILE_STATUS, &status2);
  if (status2 == GL_FALSE) {
    printf("Oh no, error: %d :(\n", status2);
    GLint logLength;
    glGetShaderiv(vert, GL_INFO_LOG_LENGTH, &logLength);

    char *str = static_cast<char *>(malloc(logLength + 1));
    memset(str, 'a', logLength);
    str[logLength] = '\0';
    glGetShaderInfoLog(vert, logLength, nullptr, str);

    printf("error: %s\n", str);
  }

  err = glGetError();
  if (err != GL_NO_ERROR) {
    printf("GL ERROR: %d\n", err);
  }

  program = glCreateProgram();
  glAttachShader(program, frag);
  glAttachShader(program, vert);

  glLinkProgram(program);
  glDetachShader(program, vert);
  glDetachShader(program, frag);

  intermediateProgram = glCreateProgram();
  glAttachShader(intermediateProgram, frag2);
  glAttachShader(intermediateProgram, vert);

  glLinkProgram(intermediateProgram);
  glDetachShader(intermediateProgram, vert);
  glDetachShader(intermediateProgram, frag2);

  glDeleteShader(vert);
  glDeleteShader(frag);
  glDeleteShader(frag2);

  err = glGetError();
  if (err != GL_NO_ERROR) {
    printf("GL ERROR: %d\n", err);
  }

  glGenTextures(1, &tex);
  glBindTexture(GL_TEXTURE_2D, tex);

  err = glGetError();
  if (err != GL_NO_ERROR) {
    printf("GL ERROR: %d\n", err);
  }

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

  err = glGetError();
  if (err != GL_NO_ERROR) {
    printf("GL ERROR: %d\n", err);
  }

  glBindTexture(GL_TEXTURE_2D, 0);
}

void Video::setScreenDimensions(int x2, int y2, int screenWidth,
                                int screenHeight) {
  this->x = x2;
  this->y = y2;
  this->windowWidth = screenWidth;
  this->windowHeight = screenHeight;

  glBindTexture(GL_TEXTURE_2D, intermediateTex);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, screenWidth, screenHeight, 0, GL_RGBA,
               GL_UNSIGNED_BYTE, nullptr);
  glBindTexture(GL_TEXTURE_2D, 0);

  recalcVertexArray();
}

void Video::draw() {
  glViewport(this->x, this->y, this->windowWidth, this->windowHeight);
  if (!this->hardwareRendering) {
    glBindTexture(GL_TEXTURE_2D, tex);
    glPixelStorei(GL_UNPACK_ROW_LENGTH, softwareBufPitch / 2);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, softwareBufWidth,
                 softwareBufHeight, 0, GL_RGB, GL_UNSIGNED_SHORT_5_6_5,
                 softwareBufData);

    auto err = glGetError();
    if (err != GL_NO_ERROR) {
      printf("GL ERROR software rendering: %d\n", err);
    }

    glUseProgram(FL::Graphics::Shaders::texProgram);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);

    // Bind texture with game data
    // Draw to intermediate framebuffer
    // Bind that framebuffer's texture (max resolution)
    // Bind back buffer
    // Draw texture like normal
  } else {
    glBindTexture(GL_TEXTURE_2D, otherTex); // 600 x 480 or whatever
    glUseProgram(FL::Graphics::Shaders::texProgram);
    glBindFramebuffer(GL_FRAMEBUFFER, intermediateFbo);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glBindTexture(GL_TEXTURE_2D, intermediateTex);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glUseProgram(intermediateProgram);
    glBindVertexArray(intermediateVao);
    glBindBuffer(GL_ARRAY_BUFFER, intermediateVbo);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    //            glPixelStorei(GL_UNPACK_ROW_LENGTH, softwareBufPitch / 2);
    //            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, softwareBufWidth,
    //            softwareBufHeight, 0, GL_RGB,
    //                         GL_UNSIGNED_SHORT_5_6_5,
    //                         softwareBufData);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    auto err = glGetError();
    if (err != GL_NO_ERROR) {
      printf("GL ERROR: %d\n", err);
    }

    // bind game FBO's texture
    // Draw to intermediate framebuffer
    // Bind that framebuffer's texture (max resolution)
    // Bind back buffer
    // Draw texture like normal
  }
}

void Video::refreshCoreVideo(const void *d, unsigned w, unsigned h, size_t p) {
  this->softwareBufData = d;
  this->softwareBufWidth = w;
  this->softwareBufHeight = h;
  this->softwareBufPitch = p;
}

void Video::setHardwareRenderCallback(retro_hw_render_callback *cb) {
  this->hardwareRendering = true;
  this->hardwareRenderCallback = cb;

  auto err = glGetError();
  if (err != GL_NO_ERROR) {
    printf("GL in HW render CB ERROR: %d\n", err);
  }

  this->hardwareRenderCallback->get_proc_address = [](const char *sym) {
    return (retro_proc_address_t)SDL_GL_GetProcAddress(sym);
  };
  this->hardwareRenderCallback->get_current_framebuffer = []() {
    return (uintptr_t)fboId;
  };
}

bool Video::getOverscan() const { return this->useOverscan; }

void Video::setRotation(unsigned int rot) { this->rotation = rot; }

bool Video::getAllowDupeFrames() const { return this->canDupeFrames; }

void Video::setPixelFormat(retro_pixel_format *format) {
  printf("PIXEL FORMAT: %d\n", *format);
  this->pixelFormat = format;
}

void Video::setFrameTimeCallback(retro_frame_time_callback *cb) {
  this->frameTimeCallback = cb;
}

void Video::setGameGeometry(retro_game_geometry *geo) {
  this->gameGeometry = geo;
  this->recalcVertexArray();
}

void Video::setPictureMode(PictureMode mode) {
  this->displayMode = mode;
  this->recalcVertexArray();
}

void Video::initializeHwFramebuffer() {
  // Check if game geometry is not yet set
  glGenTextures(1, &otherTex);
  glBindTexture(GL_TEXTURE_2D, otherTex);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, gameGeometry->max_width,
               gameGeometry->max_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

  glGenFramebuffers(1, &fbo);
  glBindFramebuffer(GL_FRAMEBUFFER, fbo);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
                         otherTex, 0);
  glGenRenderbuffers(1, &renderBuffer);
  glBindRenderbuffer(GL_RENDERBUFFER, renderBuffer);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24,
                        gameGeometry->max_width, gameGeometry->max_height);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
                            GL_RENDERBUFFER, renderBuffer);

  auto s = glCheckFramebufferStatus(GL_FRAMEBUFFER);
  if (s != GL_FRAMEBUFFER_COMPLETE) {
    printf("frame buffer not complete %d\n", s);
  }

  fboId = fbo;

  glBindTexture(GL_TEXTURE_2D, 0);
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  glBindRenderbuffer(GL_RENDERBUFFER, 0);

  this->hardwareRenderCallback->context_reset();
}

void Video::initialize(int x2, int y2, int screenWidth, int screenHeight) {
  this->setScreenDimensions(x2, y2, screenWidth, screenHeight);

  // TODO: game geometry should set the min size of the window
  // Update this stuff when the screen size changes
  // init intermediate stuff
  glGenTextures(1, &intermediateTex);
  glBindTexture(GL_TEXTURE_2D, intermediateTex);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, screenWidth, screenHeight, 0, GL_RGBA,
               GL_UNSIGNED_BYTE, nullptr);

  glGenFramebuffers(1, &intermediateFbo);
  glBindFramebuffer(GL_FRAMEBUFFER, intermediateFbo);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
                         intermediateTex, 0);

  auto s = glCheckFramebufferStatus(GL_FRAMEBUFFER);
  if (s != GL_FRAMEBUFFER_COMPLETE) {
    printf("frame buffer not complete %d\n", s);
  }

  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  glBindTexture(GL_TEXTURE_2D, 0);

  if (this->hardwareRendering) {
    this->initializeHwFramebuffer();
  }
}
} // namespace libretro