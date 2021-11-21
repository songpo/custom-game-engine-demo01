//
// Created by liuso on 2021/11/21.
//

#pragma once

#include <iostream>

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

};
}

