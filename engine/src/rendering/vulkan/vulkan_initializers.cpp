//
// Created by liuso on 2021/11/21.
//

#include "vulkan_initializers.h"

namespace SP {

VkCommandPoolCreateInfo VulkanInitializers::GetCommandPoolCreateInfo(
    uint32_t queueFamilyIndex,
    VkCommandPoolCreateFlags flags
) {
  VkCommandPoolCreateInfo info{VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO};
  info.flags = flags;
  info.queueFamilyIndex = queueFamilyIndex;
  return info;
}
VkCommandBufferAllocateInfo VulkanInitializers::GetCommandBufferAllocateInfo(
    VkCommandPool pool,
    uint32_t count,
    VkCommandBufferLevel level
) {
  VkCommandBufferAllocateInfo info{VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO};
  info.level = level;
  info.commandBufferCount = count;
  info.commandPool = pool;
  return info;
}
VkPipelineShaderStageCreateInfo VulkanInitializers::GetPipelineShaderStageCreateInfo(
    VkShaderStageFlagBits stage,
    VkShaderModule module
) {
  VkPipelineShaderStageCreateInfo info = {VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO};
  info.stage = stage;
  info.module = module;
  info.pName = "main";
  return info;
}
VkPipelineVertexInputStateCreateInfo VulkanInitializers::GetPipelineVertexInputStateCreateInfo() {
  VkPipelineVertexInputStateCreateInfo info{VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO};
  info.vertexAttributeDescriptionCount = 0;
  info.vertexBindingDescriptionCount = 0;
  return info;
}
VkPipelineInputAssemblyStateCreateInfo VulkanInitializers::GetPipelineInputAssemblyStateCreateInfo(VkPrimitiveTopology topology) {
  VkPipelineInputAssemblyStateCreateInfo info{VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO};
  info.topology = topology;
  info.primitiveRestartEnable = VK_FALSE;
  return info;
}
VkPipelineRasterizationStateCreateInfo VulkanInitializers::GetPipelineRasterizationStateCreateInfo(VkPolygonMode polygonMode) {
  VkPipelineRasterizationStateCreateInfo info{VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO};
  info.depthClampEnable = VK_FALSE;
  info.rasterizerDiscardEnable = VK_FALSE;

  info.polygonMode = polygonMode;
  info.lineWidth = 1.f;
  info.cullMode = VK_CULL_MODE_BACK_BIT;
  info.frontFace = VK_FRONT_FACE_CLOCKWISE;

  info.depthBiasEnable = VK_FALSE;
  info.depthBiasConstantFactor = 0.f;
  info.depthBiasSlopeFactor = 0.f;
  info.depthBiasClamp = 0.f;
  return info;
}
VkPipelineMultisampleStateCreateInfo VulkanInitializers::GetPipelineMultisampleStateCreateInfo() {
  VkPipelineMultisampleStateCreateInfo info{VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO};
  info.sampleShadingEnable = VK_FALSE;
  info.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
  info.minSampleShading = 1.f;
  info.pSampleMask = nullptr;
  info.alphaToCoverageEnable = VK_FALSE;
  info.alphaToOneEnable = VK_FALSE;
  return info;
}
VkPipelineColorBlendAttachmentState VulkanInitializers::GetPipelineColorBlendAttachmentState() {
  VkPipelineColorBlendAttachmentState state{};
  state.colorWriteMask = VK_COLOR_COMPONENT_R_BIT |
      VK_COLOR_COMPONENT_G_BIT |
      VK_COLOR_COMPONENT_B_BIT |
      VK_COLOR_COMPONENT_A_BIT;
  state.blendEnable = VK_FALSE;
  return state;
}
VkPipelineLayoutCreateInfo VulkanInitializers::GetPipelineLayoutCreateInfo() {
  VkPipelineLayoutCreateInfo info{VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO};
  info.flags = 0;
  info.setLayoutCount = 0;
  info.pSetLayouts = nullptr;
  info.pushConstantRangeCount = 0;
  info.pPushConstantRanges = nullptr;
  return info;
}

}