//
// Created by liuso on 2021/11/22.
//
#pragma once
#include <vulkan/vulkan.h>
#include <vector>

namespace SP {

class VulkanPipelineBuilder {
 public:
  std::vector<VkPipelineShaderStageCreateInfo> vector_;
};

}
