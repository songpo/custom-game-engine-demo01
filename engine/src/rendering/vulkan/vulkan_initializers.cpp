//
// Created by liuso on 2021/11/21.
//

#include "vulkan_initializers.h"

namespace SP {

VkCommandPoolCreateInfo VulkanInitializers::GetCommandPoolCreateInfo(
    uint32_t queueFamilyIndex,
    VkCommandPoolCreateFlags flags
) {
  VkCommandPoolCreateInfo commandPoolCreateInfo{VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO};
  commandPoolCreateInfo.flags = flags;
  commandPoolCreateInfo.queueFamilyIndex = queueFamilyIndex;
  return commandPoolCreateInfo;
}
VkCommandBufferAllocateInfo VulkanInitializers::GetCommandBufferAllocateInfo(
    VkCommandPool pool,
    uint32_t count,
    VkCommandBufferLevel level
) {
  VkCommandBufferAllocateInfo commandBufferAllocateInfo{VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO};
  commandBufferAllocateInfo.level = level;
  commandBufferAllocateInfo.commandBufferCount = count;
  commandBufferAllocateInfo.commandPool = pool;
  return commandBufferAllocateInfo;
}

}