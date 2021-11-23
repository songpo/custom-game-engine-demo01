//
// Created by liuso on 2021/11/22.
//

#include <iostream>
#include "vulkan_pipeline_builder.h"

namespace SP {

VkPipeline VulkanPipelineBuilder::Build(VkDevice device, VkRenderPass renderPass) {
  VkPipelineViewportStateCreateInfo
      pipelineViewportStateCreateInfo{VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO};
  pipelineViewportStateCreateInfo.viewportCount = 1;
  pipelineViewportStateCreateInfo.pViewports = &_view_port;
  pipelineViewportStateCreateInfo.scissorCount = 1;
  pipelineViewportStateCreateInfo.pScissors = &_scissor;

  VkPipelineColorBlendStateCreateInfo
      colorBlendStateCreateInfo = {VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO};
  colorBlendStateCreateInfo.logicOpEnable = VK_FALSE;
  colorBlendStateCreateInfo.logicOp = VK_LOGIC_OP_COPY;
  colorBlendStateCreateInfo.attachmentCount = 1;
  colorBlendStateCreateInfo.pAttachments = &_colorBlendAttachment;

  VkGraphicsPipelineCreateInfo graphicsPipelineCreateInfo{VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO};
  graphicsPipelineCreateInfo.stageCount = _shaderStages.size();
  graphicsPipelineCreateInfo.pStages = _shaderStages.data();
  graphicsPipelineCreateInfo.pVertexInputState = &_vertexInputState;
  graphicsPipelineCreateInfo.pInputAssemblyState = &_inputAssemblyState;
  graphicsPipelineCreateInfo.pViewportState = &pipelineViewportStateCreateInfo;
  graphicsPipelineCreateInfo.pRasterizationState = &_rasterizer;
  graphicsPipelineCreateInfo.pMultisampleState = &_multisampleState;
  graphicsPipelineCreateInfo.pColorBlendState = &colorBlendStateCreateInfo;
  graphicsPipelineCreateInfo.layout = _pipelineLayout;
  graphicsPipelineCreateInfo.renderPass = renderPass;
  graphicsPipelineCreateInfo.subpass = 0;
  graphicsPipelineCreateInfo.basePipelineHandle = VK_NULL_HANDLE;

  VkPipeline pipeline;
  if (vkCreateGraphicsPipelines(device, VK_NULL_HANDLE, 1, &graphicsPipelineCreateInfo, nullptr, &pipeline)
      != VK_SUCCESS) {
    std::cout << "Failed to create pipeline!" << std::endl;
    return VK_NULL_HANDLE;
  }
  return pipeline;
}

}
