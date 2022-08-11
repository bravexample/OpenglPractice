#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>

GLuint setupTexture(GLenum texCount, GLenum target, GLenum format, int imageWidth, int imageHeight, char *bytes){
    GLuint texture;
    glGenTextures(1, &texture);
    glActiveTexture(texCount);
    glBindTexture(target, texture);

    glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(target, 0, format, imageWidth, imageHeight, 0, format, GL_UNSIGNED_BYTE, bytes);
    glGenerateMipmap(target);

    glBindTexture(target, 0);

    return texture;
}

#endif