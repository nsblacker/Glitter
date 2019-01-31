//
// Created by HFY on 2019/1/30.
//

/**
 * In fact, we have finished what this tutorial tell us do in HelloTriangleExtend. It's a colored triangle. Differently,
 * we finish it with two VBO to pass data, aPos and aColor to vertex shader. But in this section, we finished it
 * using one VBO, and describe how to use these data through glVertexAttribPointer. What matter is the last param and
 * the second last param, indicates offset and stride, will let OpenGL know how to use it.
 * You can skip this and see others in HelloShader directory, which show Object Oriented to make shader work
 * */
#include "HelloShader.h"

#include "glitter.hpp"
#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <iostream>
#include "ShaderMgr.h"


const char *vertexShaderSource_Shader = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "layout (location = 1) in vec3 aColor;\n"
                                 "out vec3 colour;\n"
                                 "void main()\n"
                                 "{\n"
                                 "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                 "   colour = aColor;\n"
                                 "}\0";

const char *fragmentShaderSource_Shader = "#version 330 core\n"
                                   "in vec3 colour;\n"
                                   "out vec4 FragColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "   FragColor = vec4(colour, 1.0f);\n"
                                   "}\n\0";

int HelloShader::runHelloShader() {

    // Load GLFW and Create a Window
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    auto mWindow = glfwCreateWindow(mWidth, mHeight, "OpenGL", nullptr, nullptr);

    // Check for Valid Context
    if (mWindow == nullptr) {
        fprintf(stderr, "Failed to Create OpenGL Context");
        return EXIT_FAILURE;
    }

    // Create Context and Load OpenGL Functions
    glfwMakeContextCurrent(mWindow);
    gladLoadGL();
    fprintf(stderr, "OpenGL %s\n", glGetString(GL_VERSION));


    ShaderMgr shaderMgr;
    shaderMgr.attach(vertexShaderSource_Shader, ShaderMgr::ShaderType::Vertex);
    shaderMgr.attach(fragmentShaderSource_Shader, ShaderMgr::ShaderType::Fragment);

    // Set up vertex data (and buffer(s)) and configure vertex attributes
    float vertices[] = {
            -0.5f, -0.5f, 0.0f,     1.0f,0.0f,0.0f,
            0.5f, -0.5f, 0.0f,      0.0f,1.0f,0.0f,
            0.0f, 0.5f, 0.0f,       0.0f,0.0f,1.0f
    };

    unsigned int VAO,VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


    // Now we have data(vertices) should be rendered and how to use it(shader),  now we should tell OpenGL what param
    // these data should link to.
    unsigned int aPosLocation = glGetAttribLocation(shaderMgr.getProgram(), "aPos");// what it is in vertex shader. can also be got via glGetAttribLocation
    glVertexAttribPointer(aPosLocation, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(aPosLocation);

    unsigned int aColorLocation = glGetAttribLocation(shaderMgr.getProgram(), "aColor");
    glVertexAttribPointer(aColorLocation, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(aColorLocation);

    // Rendering Loop
    while (glfwWindowShouldClose(mWindow) == false) {
        if (glfwGetKey(mWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(mWindow, true);

        // Background Fill Color
        glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Render
        shaderMgr.useProgram();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);


        // Flip Buffers and Draw
        glfwSwapBuffers(mWindow);
        glfwPollEvents();
    }

    // De-allocate
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);


    // Terminate
    glfwTerminate();
    return EXIT_SUCCESS;
}

