//
// Created by liuso on 2021/11/20.
//

#include <stdexcept>
#include <iostream>
#include "multiplatform_window.h"

namespace SP {

MultiPlatformWindow::MultiPlatformWindow() {
  _window = nullptr;
}
void MultiPlatformWindow::OpenWindow(WindowData data) {
  glfwInit();

  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

  _window = glfwCreateWindow(static_cast<int>(data.width),
                             static_cast<int>(data.height),
                             data.title.c_str(),
                             nullptr,
                             nullptr);
}
bool MultiPlatformWindow::Update() {
  glfwPollEvents();

  return glfwWindowShouldClose(_window);
}
std::pair<int, int> MultiPlatformWindow::GetWindowExtents() {
  int width = 0;
  int height = 0;
  glfwGetFramebufferSize(_window, &width, &height);

  return {width, height};
}
void MultiPlatformWindow::RequestDrawSurface(std::unordered_map<SurfaceArgs, std::any> args) {
  // Extract what we need
  try {
    auto vkInstance = std::any_cast<VkInstance>(args[SurfaceArgs::INSTANCE]);
    auto *allocationCallbacks = args[SurfaceArgs::ALLOCATORS].has_value()
                                ? std::any_cast<VkAllocationCallbacks *>(args[SurfaceArgs::ALLOCATORS])
                                : nullptr;
    auto *surface = std::any_cast<VkSurfaceKHR *>(args[SurfaceArgs::OUT_SURFACE]);

    if (vkInstance == VK_NULL_HANDLE) {
      throw std::runtime_error("Must provide an instance!");
    }

    VkResult vkResult = glfwCreateWindowSurface(vkInstance, _window, allocationCallbacks, surface);
    if (vkResult != VK_SUCCESS) {
      throw std::runtime_error("Failed to create window surface!");
    }
  } catch (std::bad_any_cast &e) {
    std::cout << "Failed to cast window surface arguments: " << e.what() << std::endl;
  }
}

}
