//
// Created by HFY on 2019/1/29.
//
// Local Headers
#define STB_IMAGE_IMPLEMENTATION
#include "glitter.hpp"

// Standard Headers
#include <cstdio>
#include <cstdlib>

#include "HelloWindow.h"

int HelloWindow::runHelloWindow() {
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


        // Build and Compile Shader Program
        ;
        ;
        ;


        // Rendering Loop
        while (glfwWindowShouldClose(mWindow) == false) {
            if (glfwGetKey(mWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
                glfwSetWindowShouldClose(mWindow, true);

            // Background Fill Color
            glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            // Render
            ;
            ;
            ;


            // Flip Buffers and Draw
            glfwSwapBuffers(mWindow);
            glfwPollEvents();
        }

        // De-allocate
        ;
        ;
        ;


        // Terminate
        glfwTerminate();
        return EXIT_SUCCESS;
}