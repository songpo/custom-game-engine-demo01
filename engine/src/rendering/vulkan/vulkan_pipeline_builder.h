//
// Created by liuso on 2021/11/22.
//
#pragma once
#include <vulkan/vulkan.h>
#include <vector>

namespace SP {

class VulkanPipelineBuilder {
 public:
  std::vector<VkPipelineShaderStageCreateInfo> _shaderStages;
  VkPipelineVertexInputStateCreateInfo _vertexInputState;
  VkPipelineInputAssemblyStateCreateInfo _inputAssemblyState;
  VkViewport _view_port;
  VkRect2D _scissor;

  VkPipelineRasterizationStateCreateInfo _rasterizer;
  VkPipelineColorBlendAttachmentState _colorBlendAttachment;
  VkPipelineMultisampleStateCreateInfo _multisampleState;
  VkPipelineLayout _pipelineLayout;

  VkPipeline Build(VkDevice device, VkRenderPass renderPass);
};

}
