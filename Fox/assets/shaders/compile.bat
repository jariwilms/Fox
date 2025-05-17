@echo off
set shader=%1
set vulkan_sdk_path=C:/VulkanSDK/1.3.296.0
set compiler_path=%vulkan_sdk_path/Bin/%
set compiler_exe=glslc.exe
set flags=-Werror -O
set command=%compiler_path%%compiler_exe% %flags%

cls

echo ---- SPIR-V COMPILER -----
echo:
echo Compiler: %compiler_exe%
echo:

IF EXIST source/%shader%.vert (
    echo Compiling %shader%.vert
    %command% source/%shader%.vert -o compiled/%shader%.vert.spv
    IF ERRORLEVEL 1 (
        echo Error compiling vertex shader: %shader%.vert
    ) ELSE (
        echo Compiled successfully
    )
) ELSE (
    echo Shader not found: %shader%.vert
)
echo:

IF EXIST source/%shader%.geom (
    echo Compiling %shader%.geom
    %command% source/%shader%.geom -o compiled/%shader%.geom.spv
    IF ERRORLEVEL 1 (
        echo Error compiling geometry shader: %shader%.geom
    ) ELSE (
        echo Compiled successfully
    )
) ELSE (
    echo Shader not found: %shader%.geom
)
echo:

IF EXIST source/%shader%.frag (
    echo Compiling %shader%.frag
    C:/VulkanSDK/1.3.296.0/Bin/glslc.exe -Werror -O source/%shader%.frag -o compiled/%shader%.frag.spv
    IF ERRORLEVEL 1 (
        echo Error compiling fragment shader: %shader%.frag
    ) ELSE (
        echo Compiled successfully
    )
) ELSE (
    echo Shader not found: %shader%.frag
)

echo:
echo --------------------------
