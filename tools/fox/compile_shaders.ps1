param([string]$Shader = "")

# Configuration
$Vendor          = "LunarG"
$VendorDirectory = "..\..\vendor\lunarg"
$Compiler        = "glslc.exe"
$Flags           = @("-Werror", "-O")
$ShaderDirectory = "..\..\fox\assets\shaders"
$SourceDirectory = "$ShaderDirectory\source"
$OutputDirectory = "$ShaderDirectory\compiled"

# Shader extensions and their display names
$ShaderTypes = [ordered] @{
    ".vert" = "vertex"
    ".tesc" = "tessellation control"
    ".tese" = "tessellation evaluation"
    ".geom" = "geometry" 
    ".frag" = "fragment"
}

function Compile-Shader 
{
    param([string]$ShaderName)
    
    Write-Host "$ShaderName" -ForegroundColor Yellow
    
    foreach ($Extension in $ShaderTypes.Keys) 
    {
        $DisplayName = $ShaderTypes[$Extension]
        $SourceFile  = Join-Path $SourceDirectory "$ShaderName$Extension"
        $OutputFile  = Join-Path $OutputDirectory "$ShaderName$Extension.spv"
        
        if (Test-Path $SourceFile) 
        {
            $CompilerPath = Join-Path $VendorDirectory $Compiler
            $Arguments    = $Flags + @($SourceFile, "-o", $OutputFile)
            
            $Error  = &$CompilerPath $Arguments 2>&1
            $Result = [string]$Error

            if ($LastExitCode -eq 0) 
            {
                Write-Host "   $ShaderName$Extension" -ForegroundColor Green
            }
            else 
            {
                $Value = $Result.SubString($Result.IndexOf("error: "))

                Write-Host "    $ShaderName$Extension" -ForegroundColor Red
                Write-Host "    $Value"
            }
        }
    }

    Write-Host ""
}

function Get-UniqueShaderNames
{
    $UniqueNames = @()
    
    foreach ($Extension in $ShaderTypes.Keys) 
    {
        $Pattern = Join-Path $SourceDirectory "*$Extension"
        $Files = Get-ChildItem -Path $Pattern -ErrorAction SilentlyContinue
        
        foreach ($File in $Files) 
        {
            $BaseName = $File.BaseName.Replace($Extension.Substring(1), "")

            if ($BaseName -notin $UniqueNames) 
            {
                $UniqueNames += $BaseName
            }
        }
    }
    
    return $UniqueNames
}

function Main
{
    # Main execution
    Clear-Host
    Write-Host "----- SPIR-V COMPILER -----" -ForegroundColor Red
    Write-Host ""
    Write-Host "Vendor  : $Vendor"   -ForegroundColor Yellow
    Write-Host "Compiler: $Compiler" -ForegroundColor Yellow
	Write-Host ""

    # Ensure compiled directory exists
    if (!(Test-Path $OutputDirectory)) 
    {
        New-Item -ItemType Directory -Path $OutputDirectory -Force | Out-Null
        Write-Host "Created output directory: $OutputDirectory" -ForegroundColor Green
        Write-Host ""
    }

    if ([string]::IsNullOrEmpty($Shader)) 
    {
        Write-Host "Compiling all shaders in source folder..." -ForegroundColor Yellow
    
        $UniqueShaders = Get-UniqueShaderNames
    
        if ($UniqueShaders.Count -eq 0) 
        {
            Write-Host "No shader files found in $SourceDirectory" -ForegroundColor Red
        } 
        else 
        {
            Write-Host "Found $($UniqueShaders.Count) unique shader(s)" -ForegroundColor Yellow
            Write-Host ""
        
            foreach ($ShaderName in $UniqueShaders) 
            {
                Compile-Shader -ShaderName $ShaderName
            }
        }
    } 
    else 
    {
        Compile-Shader -ShaderName $Shader
    }

    Write-Host "---------------------------"  -ForegroundColor Red
    Write-Host "Press any key to continue..." -ForegroundColor Yellow

    $null = $Host.UI.RawUI.ReadKey("NoEcho,IncludeKeyDown")
}

Main
