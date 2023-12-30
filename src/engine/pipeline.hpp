#pragma once

#include <string>
#include <vector>

#include "engine/device.hpp"


namespace ve {

    struct PipelineConfigInfo {

        VkPipelineViewportStateCreateInfo viewportInfo;
        VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo;
        VkPipelineRasterizationStateCreateInfo rasterizationInfo;
        VkPipelineMultisampleStateCreateInfo multisampleInfo;
        VkPipelineColorBlendAttachmentState colorBlendAttachment;
        VkPipelineColorBlendStateCreateInfo colorBlendInfo;
        VkPipelineDepthStencilStateCreateInfo depthStencilInfo;
        std::vector<VkDynamicState> dynamicStateEnables;
        VkPipelineDynamicStateCreateInfo dynamicStateInfo;
        VkPipelineLayout pipelineLayout = nullptr;
        VkRenderPass renderPass = nullptr;
        uint32_t subpass = 0;
    };

    class Pipeline {
    public:
        Pipeline(
            Device& device,
            const std::string&& vertFile,
			const std::string&& geomFile,
            const std::string&& fragFile,
            const PipelineConfigInfo& configInfo);
        Pipeline(const Pipeline&) = delete;
        Pipeline& operator=(const Pipeline&) = delete;
        ~Pipeline();

        void bind(VkCommandBuffer commandBuffer);
        static void defaultPipelineConfigInfo(PipelineConfigInfo& configInfo);

    private:
        static std::vector<char> readFile(const std::string& filename);
        void createGraphicsPipeline(
				const std::string&& vertFile,
				const std::string&& geomFile,
				const std::string&& fragFile,
				const PipelineConfigInfo& configInfo);
        void createShaderModule(const std::vector<char>& code, VkShaderModule* shaderModule);

        Device& device_;
        VkPipeline graphicsPipeline;

        VkShaderModule vertShaderModule;
		VkShaderModule geomShaderModule;
        VkShaderModule fragShaderModule;
    };

} // ve
