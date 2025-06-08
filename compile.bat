@echo off
set shader=%1
set vendor_path=vendor\lunarg\
set compiler=glslc.exe
set flags=-Werror -O
set source_path=Fox\assets\shaders\source\
set compiled_path=Fox\assets\shaders\compiled\
set command=%vendor_path%%compiler% %flags%
set vertex_ext=.vert
set geometry_ext=.geom
set tess_ctrl_ext=.tesc
set tess_eval_ext=.tese
set fragment_ext=.frag



cls

echo ---- SPIR-V COMPILER -----
echo:
echo Compiler: %compiler%
echo:

IF EXIST %source_path%%shader%%vertex_ext% (
    echo Compiling %shader%%vertex_ext%
    %command% %source_path%%shader%%vertex_ext% -o %compiled_path%%shader%%vertex_ext%.spv
    IF ERRORLEVEL 1 (
        echo Error compiling vertex shader: %shader%%vertex_ext%
    ) ELSE (
        echo Compiled successfully
    )
) ELSE (
    echo Shader not found: %shader%%vertex_ext%
)
echo:

IF EXIST %source_path%%shader%%geometry_ext% (
    echo Compiling %shader%%geometry_ext%
    %command% %source_path%%shader%%geometry_ext% -o %compiled_path%%shader%%geometry_ext%.spv
    IF ERRORLEVEL 1 (
        echo Error compiling vertex shader: %shader%%geometry_ext%
    ) ELSE (
        echo Compiled successfully
    )
) ELSE (
    echo Shader not found: %shader%%geometry_ext%
)
echo:

IF EXIST %source_path%%shader%%tess_ctrl_ext% (
    echo Compiling %shader%%tess_ctrl_ext%
    %command% %source_path%%shader%%tess_ctrl_ext% -o %compiled_path%%shader%%tess_ctrl_ext%.spv
    IF ERRORLEVEL 1 (
        echo Error compiling vertex shader: %shader%%tess_ctrl_ext%
    ) ELSE (
        echo Compiled successfully
    )
) ELSE (
    echo Shader not found: %shader%%tess_ctrl_ext%
)
echo:

IF EXIST %source_path%%shader%%tess_eval_ext% (
    echo Compiling %shader%%tess_eval_ext%
    %command% %source_path%%shader%%tess_eval_ext% -o %compiled_path%%shader%%tess_eval_ext%.spv
    IF ERRORLEVEL 1 (
        echo Error compiling vertex shader: %shader%%tess_eval_ext%
    ) ELSE (
        echo Compiled successfully
    )
) ELSE (
    echo Shader not found: %shader%%tess_eval_ext%
)
echo:

IF EXIST %source_path%%shader%%fragment_ext% (
    echo Compiling %shader%%fragment_ext%
    %command% %source_path%%shader%%fragment_ext% -o %compiled_path%%shader%%fragment_ext%.spv
    IF ERRORLEVEL 1 (
        echo Error compiling vertex shader: %shader%%fragment_ext%
    ) ELSE (
        echo Compiled successfully
    )
) ELSE (
    echo Shader not found: %shader%%fragment_ext%
)

echo:
echo --------------------------
