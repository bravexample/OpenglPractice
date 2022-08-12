#include <math.h>
#include <program.h>
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

int WinMain(){
    if(!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    int imageWidth, imageHeight, colorChannel;
    char *bytes = stbi_load("image/1.png", &imageWidth, &imageHeight, &colorChannel, 0);
    if(!bytes){
        glfwTerminate();
        return -1;
    }

    int windowWidth = imageWidth/2, windowHeight = imageHeight/2;
    GLFWwindow *window = glfwCreateWindow(windowWidth, windowHeight, "OpenglPractice", 0, 0);
    if(!window){
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    gladLoadGL();
    glViewport(0, 0, windowWidth, windowHeight);

    GLuint program = setupProgram("shader/vertex", "shader/fragment");

    GLfloat vertices[] ={
        -1.0f,  -1.0f,  0.0f, 0.0f, 1.0f,
        1.0f,   -1.0f,  0.0f, 1.0f, 1.0f,
        1.0f,   1.0f,   0.0f, 1.0f, 0.0f,
        -1.0f,  1.0f,   0.0f, 0.0f, 0.0f
    };

    GLuint indices[] ={
        0, 1, 2,
        0, 2, 3
    };

    GLuint vertexArray, arrayBuffer, elementArraybuffer;

    glGenVertexArrays(1, &vertexArray);
    glBindVertexArray(vertexArray);

    glGenBuffers(1, &arrayBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, arrayBuffer);
    glNamedBufferData(arrayBuffer, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &elementArraybuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementArraybuffer);
    glNamedBufferData(elementArraybuffer, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), 0);
    glEnableVertexAttribArray(0);
    //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void *)(3*sizeof(float)));
    //glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void *)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    GLuint scale = glGetUniformLocation(program, "scale");

    GLuint texture = setupTexture(GL_TEXTURE0, GL_TEXTURE_2D, colorChannel+6404, imageWidth, imageHeight, bytes);

    stbi_image_free(bytes);

    GLuint tex0Uni = glGetUniformLocation(program, "tex0");
    glUseProgram(program);
    glUniform1i(tex0Uni, 0);

    while(!glfwWindowShouldClose(window)){
        //glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        //glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(program);
        glUniform1f(scale, 0.0f);
        glBindTexture(GL_TEXTURE_2D, texture);
        glBindVertexArray(vertexArray);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &vertexArray);
    glDeleteBuffers(1, &arrayBuffer);
    glDeleteBuffers(1, &elementArraybuffer);
    glDeleteTextures(1, &texture);
    glDeleteProgram(program);
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
