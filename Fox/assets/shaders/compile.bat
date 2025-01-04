set shader=%1

cls

C:/VulkanSDK/1.3.296.0/Bin/glslc.exe -Werror -O source/%shader%.vert -o compiled/%shader%.vert.spv
C:/VulkanSDK/1.3.296.0/Bin/glslc.exe -Werror -O source/%shader%.frag -o compiled/%shader%.frag.spv
