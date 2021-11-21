//
// Created by liuso on 2021/11/21.
//

#pragma once

#include <iostream>
#include <vulkan/vulkan.h>

using namespace std;

#define VK_CHECK(x)                                                               \
  do {                                                                            \
     VkResult err = x;                                                            \
     if (err) {                                                                   \
       std::cout << "Detected vulkan error: " << err << std::endl;                \
       abort();                                                                   \
     }                                                                            \
  } while(0)

namespace SP {

class VulkanUtilities {
 public:
  static bool LoadShaderModule(const std::string &file_path, VkDevice device, VkShaderModule &outShaderModule);
};

}

