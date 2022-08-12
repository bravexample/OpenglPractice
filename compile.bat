@echo off
cl /O2 /favor:blend /std:c17 /Iinclude /Fe:release.exe source\glad.c main.c /link /NODEFAULTLIB:MSVCRT lib\glfw3dll.lib OpenGL32.lib
del *obj
