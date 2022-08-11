all:
	gcc -std=c11 -mwindows -msse2 -O3 -I include -l opengl32 glfw3.dll glad.dll stb.dll -o release.exe main.c

glad:
	gcc -std=c11 -msse2 -O3 -fPIC -shared -I include -l opengl32 -o glad.dll source/glad.c

stb:
	gcc -std=c11 -msse2 -O3 -fPIC -shared -I include -l opengl32 -o stb.dll source/stb.c