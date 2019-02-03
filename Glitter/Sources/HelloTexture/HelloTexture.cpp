//
// Created by HFY on 2019/1/31.
//

#include "HelloTexture.h"
// Local Headers
#define STB_IMAGE_IMPLEMENTATION
#include "glitter.hpp"


// Standard Headers
#include <cstdio>
#include <cstdlib>

int HelloTexture::runHelloTexture() {
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

    std::string vertFile = "/Users/hfy/NSblacker/Code/Glitter/Glitter/Media/Shaders/rectangle_box.vert";
    std::string fragFile = "/Users/hfy/NSblacker/Code/Glitter/Glitter/Media/Shaders/rectangle_box.frag";
    ShaderMgr shaderMgr;
    shaderMgr.attach(vertFile, ShaderMgr::ShaderType::Vertex);
    shaderMgr.attach(fragFile, ShaderMgr::ShaderType::Fragment);
    
    // texture
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    int width, height, channels;
    //std::string fileNameString = "/Users/hfy/NSblacker/Code/Glitter/Glitter/Media/Images/container.jpg";
    //char const * fileName = fileNameString.c_str();
    char const * fileName = "/Users/hfy/NSblacker/Code/Glitter/Glitter/Media/Images/container.jpg";
    unsigned char *data = stbi_load(fileName, &width, &height, &channels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,  GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "load texel error" << std::endl;
    }


    // Set up vertex data (and buffer(s)) and configure vertex attributes
    float vertices[] = {
        //     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
            0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
            0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
            -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
            -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
    };

    int  indices [] = {
            0,1,3,
            1,2,3
    };

    unsigned int VAO,VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Now we have data(vertices) should be rendered and how to use it(shader),  now we should tell OpenGL what param
    // these data should link to.
    unsigned int aPosLocation = glGetAttribLocation(shaderMgr.getProgram(), "aPos");// what it is in vertex shader. can also be got via glGetAttribLocation
    glVertexAttribPointer(aPosLocation, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(aPosLocation);

    unsigned int aColorLocation = glGetAttribLocation(shaderMgr.getProgram(), "aColor");
    glVertexAttribPointer(aColorLocation, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(aColorLocation);

    unsigned int aTexelCoord = glGetAttribLocation(shaderMgr.getProgram(), "aTexelCoord");
    glVertexAttribPointer(aTexelCoord, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(aTexelCoord);

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
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


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
