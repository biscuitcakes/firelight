//
// Created by alexs on 11/7/2023.
//

#ifndef FIRELIGHT_DRIVER_HPP
#define FIRELIGHT_DRIVER_HPP

#include <string>
namespace FL::Graphics {

class Driver {
public:
  void drawRectangle(int x, int y, int w, int h);
  void drawText(std::string text, int x, int y);
};

} // namespace FL::Graphics

#endif // FIRELIGHT_DRIVER_HPP
