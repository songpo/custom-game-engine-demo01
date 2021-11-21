//
// Created by liuso on 2021/11/21.
//

#include "vulkan_utilities.h"
#include <fstream>
#include <vector>

namespace SP {

bool VulkanUtilities::LoadShaderModule(const string &file_path, VkDevice device, VkShaderModule &outShaderModule) {
  std::ifstream file(file_path.c_str(), std::ios::ate | std::ios::binary);

  if (!file.is_open()) {
    // TODO error logging?
    return false;
  }

  size_t fileSize = static_cast<size_t>(file.tellg());
  std::vector<uint32_t> buffer(fileSize / sizeof(uint32_t));

  file.seekg(0);
  file.read(reinterpret_cast<char *>(buffer.data()), fileSize);
  file.close();

  VkShaderModuleCreateInfo shaderModuleCreateInfo{VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO};
  shaderModuleCreateInfo.codeSize = buffer.size() * sizeof(uint32_t);
  shaderModuleCreateInfo.pCode = buffer.data();

  VkShaderModule shaderModule;
  if (vkCreateShaderModule(device, &shaderModuleCreateInfo, nullptr, &shaderModule) != VK_SUCCESS) {
    // TODO logging a problem
    return false;
  }
  outShaderModule = shaderModule;
  return true;
}
}