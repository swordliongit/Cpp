- Using CMAKE and having this option will automatically create a ==compile_commands.json== when you compile. And Clangd will use it to provide code completion.:
	- set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
- But if the file is not getting created, create it manually:
```json
[
{
  "directory": "C:/Workspace/Programming/Cpp/Experimental/build",
  "command": "C:\\mingw64\\bin\\g++.exe   -g -std=gnu++20 -o CMakeFiles\\main.dir\\main.cpp.obj -c C:\\Workspace\\Programming\\Cpp\\Experimental\\src\\main.cpp",
  "file": "C:/Workspace/Programming/Cpp/Experimental/src/main.cpp",
  "output": "CMakeFiles/main.dir/main.cpp.obj"
}
]
```
- "command" has to be found using this CMAKE command and looking at the compile output:
	- set(CMAKE_VERBOSE_MAKEFILE ON)