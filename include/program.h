#ifndef PROGRAM_H
#define PROGRAM_H

#include <stdio.h>
#include <stdlib.h>
#include <texture.h>

const char *readFile(const char *filename){
    FILE *file = fopen(filename, "rb");
    if(!file)
        exit(EXIT_FAILURE);

    long int filesize = 0;
    fseek(file, 0, SEEK_END);
    filesize = ftell(file);

    char *content = malloc(filesize+1);
    fseek(file, 0, SEEK_SET);
    fread(content, filesize, 1, file);
    fclose(file);
    content[filesize] = 0;
    return content;
}

GLuint setupProgram(const char *vertexFile, const char *fragmentFile){
    const char *vertexSource = readFile(vertexFile);
    const char *fragmentSource = readFile(fragmentFile);

    GLint state = 0;

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, 0);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &state);
    if(state == GL_FALSE)
        exit(EXIT_FAILURE);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, 0);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &state);
    if(state == GL_FALSE)
        exit(EXIT_FAILURE);

    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    free((char *)vertexSource);
    free((char *)fragmentSource);
    return program;
}

#endif