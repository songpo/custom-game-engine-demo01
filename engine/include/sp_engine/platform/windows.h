//
// Created by liuso on 2021/11/20.
//

#pragma once
#include <string>

namespace SP {

struct WindowData {
  std::string title;
  uint32_t width;
  uint32_t height;
};

class Window {
 public:
  virtual void OpenWindow(WindowData window_data) = 0;
  virtual bool Update() = 0;
};

}


