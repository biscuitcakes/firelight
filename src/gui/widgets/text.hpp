//
// Created by alexs on 11/6/2023.
//

#ifndef BLUEMBER_TEXT_HPP
#define BLUEMBER_TEXT_HPP

#include "widget.hpp"
#include <string>
namespace FL::GUI {

class Text : public Widget {
public:
  Text(std::string text, int x, int y, int w, int h);
  void render(OpenGLPainter *painter) override;

private:
  std::string text;
};

} // namespace FL::GUI

#endif // BLUEMBER_TEXT_HPP
