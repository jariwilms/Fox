set shader=%1

C:/VulkanSDK/1.3.236.0/Bin/glslc.exe source/%shader%.vert -o compiled/%shader%vert.spv
C:/VulkanSDK/1.3.236.0/Bin/glslc.exe source/%shader%.frag -o compiled/%shader%frag.spv
