@echo off
cl /O2 /favor:blend /Iinclude /Fe:release.exe source\glad.c main.c /link /NODEFAULTLIB:MSVCRT lib\glfw3dll.lib OpenGL32.lib
del *obj