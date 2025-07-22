# Fox Engine
A C++ Game Engine

## Setup
### Prerequisites
The following tools are required:
- Git
- PowerShell

### Clone the repository
```
git clone --recurse-submodules https://github.com/jariwilms/fox.git fox
```

### Generate Project Files:
```
cd fox
generate.bat
```

### Shader Compilation
```
tools\fox\compile_shaders.bat
```
This will be set as a post-build command in the future

## Optional Steps
### Using Uncrustify
Uncrustify is a code beautifier for C++.<br>
If you wish to use it for code formatting, you can register a keybind in Visual Studio with the following steps:

#### Create an external tool
```
Visual Studio > Tools > External Tools... > Add
  - Title: Uncrustify
  - Command: tools\uncrustify\uncrustify.exe
  - Arguments: -c $(SolutionDir)tools\uncrustify\uncrustify.cfg -l CPP --replace $(ItemPath)
  - Initial directory: $(ItemDir)
  - [v] Use Output Window
```

#### Register a keybind
```
Visual Studio > Tools > Options > Environment > Keyboard
Search for: "Tools.ExternalCommand"
Assign a shortcut key to your liking
```
Note that the Tools.ExternalCommand number needs to be equal to the command's index in the external tools list
