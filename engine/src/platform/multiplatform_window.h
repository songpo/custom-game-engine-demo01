//
// Created by liuso on 2021/11/20.
//
#pragma once
#define GLFW_INCLUDE_VULKAN

#include <any>
#include <GLFW/glfw3.h>
#include "sp_engine/platform/windows.h"

namespace SP {

class MultiPlatformWindow : public Window {
 public:
  MultiPlatformWindow();
  void OpenWindow(WindowData) override;
  bool Update() override;
  std::pair<int, int> GetWindowExtents() override;
  void RequestDrawSurface(std::unordered_map<SurfaceArgs, std::any>) override;
 private:
  GLFWwindow *_window;
};

};
