//
// Created by liuso on 2021/11/20.
//

#include "multiplatform_window.h"

namespace SP {

MultiPlatformWindow::MultiPlatformWindow() {
  _window = nullptr;
}
void MultiPlatformWindow::OpenWindow(WindowData window_data) {
  glfwInit();

  _window = glfwCreateWindow(window_data.width, window_data.height, window_data.title.c_str(), nullptr, nullptr);
}
bool MultiPlatformWindow::Update() {
  glfwPollEvents();

  return glfwWindowShouldClose(_window);
}
}
