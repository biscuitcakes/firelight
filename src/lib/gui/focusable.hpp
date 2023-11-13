//
// Created by alexs on 11/11/2023.
//

#ifndef FIRELIGHT_FOCUSABLE_HPP
#define FIRELIGHT_FOCUSABLE_HPP

namespace FL::GUI {

class Focusable {
public:
  enum class FocusState { NONE, PARTIAL, FULL };
  virtual ~Focusable() = default;
  virtual void gainFocus() = 0;
  virtual void loseFocus() = 0;
  virtual bool hasFocus() const = 0;
};

} // namespace FL::GUI

#endif // FIRELIGHT_FOCUSABLE_HPP
