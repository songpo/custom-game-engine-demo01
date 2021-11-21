//
// Created by liuso on 2021/11/21.
//

#pragma once

#include <vulkan/vulkan.h>

namespace SP {

class VulkanInitializers {
 public:
  static VkCommandPoolCreateInfo GetCommandPoolCreateInfo(
      uint32_t queueFamilyIndex,
      VkCommandPoolCreateFlags flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT
  );

  static VkCommandBufferAllocateInfo GetCommandBufferAllocateInfo(
      VkCommandPool pool,
      uint32_t count = 1,
      VkCommandBufferLevel level = VK_COMMAND_BUFFER_LEVEL_PRIMARY
  );
};

}
