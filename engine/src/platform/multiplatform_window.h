//
// Created by liuso on 2021/11/20.
//

#include "sp_engine/platform/windows.h"
#include <GLFW/glfw3.h>

namespace SP {

 class MultiPlatformWindow : public Window {
 public:
  MultiPlatformWindow();
  void OpenWindow(WindowData window_data) override;
  bool Update() override;

 private:
  GLFWwindow *_window;
};

};
