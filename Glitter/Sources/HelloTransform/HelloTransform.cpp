//
// Created by HFY on 2019/2/11.
//

#include "HelloTransform.h"
#include "glitter.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

int HelloTransform::runHelloTransform() {
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

    std::string vertFile = "../../Glitter/Media/Shaders/rectangle_trans.vert";
    std::string fragFile = "../../Glitter/Media/Shaders/rectangle_trans.frag";
    ShaderMgr shaderMgr;
    shaderMgr.attach(vertFile, ShaderMgr::ShaderType::Vertex);
    shaderMgr.attach(fragFile, ShaderMgr::ShaderType::Fragment);

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


    // texture1
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    int width, height, channels;
    char const * fileName = "../../Glitter/Media/Images/container.jpg";
    unsigned char *data = stbi_load(fileName, &width, &height, &channels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,  GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "load texel error" << std::endl;
    }

    // texture2
    GLuint  texture2;
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    char const * fileName2 = "../../Glitter/Media/Images/awesomeface.png";
    unsigned char *data2 = stbi_load(fileName2, &width, &height, &channels, 0);
    if (data2) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,  GL_UNSIGNED_BYTE, data2);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "load texel2 error" << std::endl;
    }

    shaderMgr.useProgram();
    glUniform1i(glGetUniformLocation(shaderMgr.getProgram(), "inputImageTexture"), 0);
    glUniform1i(glGetUniformLocation(shaderMgr.getProgram(), "inputImageTexture2"), 1);

    // 先旋转，再缩放
    glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);//这个变量用于debug，验证trans的正确定
    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
    trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));
    vec = trans * vec;
    //std::cout << vec.x << vec.y << vec.z << std::endl;
    GLuint transformLoc = glGetUniformLocation(shaderMgr.getProgram(), "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));


    // Rendering Loop
    while (glfwWindowShouldClose(mWindow) == false) {
        if (glfwGetKey(mWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(mWindow, true);

        // Background Fill Color
        glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Render
        shaderMgr.useProgram();

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        glBindVertexArray(VAO);
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

int HelloTransform::runHelloTransformRotateRepeatly() {
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

    std::string vertFile = "../../Glitter/Media/Shaders/rectangle_trans.vert";
    std::string fragFile = "../../Glitter/Media/Shaders/rectangle_trans.frag";
    ShaderMgr shaderMgr;
    shaderMgr.attach(vertFile, ShaderMgr::ShaderType::Vertex);
    shaderMgr.attach(fragFile, ShaderMgr::ShaderType::Fragment);

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

    // texture1
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    int width, height, channels;
    char const * fileName = "../../Glitter/Media/Images/container.jpg";
    unsigned char *data = stbi_load(fileName, &width, &height, &channels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,  GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "load texel error" << std::endl;
    }

    // texture2
    GLuint  texture2;
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    char const * fileName2 = "../../Glitter/Media/Images/awesomeface.png";
    unsigned char *data2 = stbi_load(fileName2, &width, &height, &channels, 0);
    if (data2) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,  GL_UNSIGNED_BYTE, data2);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "load texel2 error" << std::endl;
    }

    shaderMgr.useProgram();
    glUniform1i(glGetUniformLocation(shaderMgr.getProgram(), "inputImageTexture"), 0);
    glUniform1i(glGetUniformLocation(shaderMgr.getProgram(), "inputImageTexture2"), 1);

    // 先旋转，再缩放
    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
    trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));
    GLuint transformLoc = glGetUniformLocation(shaderMgr.getProgram(), "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));


    // Rendering Loop
    while (glfwWindowShouldClose(mWindow) == false) {
        if (glfwGetKey(mWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(mWindow, true);

        // Background Fill Color
        glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Render
        shaderMgr.useProgram();

        // 每次渲染重新生成旋转矩阵，注释调这里会很奇妙
        glm::mat4 trans = glm::mat4(1.0f);
        trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f)); // switch the order
        trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0, 0.0, 1.0)); // switch the order

        GLuint transformLoc = glGetUniformLocation(shaderMgr.getProgram(), "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        glBindVertexArray(VAO);
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

int HelloTransform::runHelloTransformTwoBoxes() {
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

    std::string vertFile = "../../Glitter/Media/Shaders/rectangle_trans.vert";
    std::string fragFile = "../../Glitter/Media/Shaders/rectangle_trans.frag";
    ShaderMgr shaderMgr;
    shaderMgr.attach(vertFile, ShaderMgr::ShaderType::Vertex);
    shaderMgr.attach(fragFile, ShaderMgr::ShaderType::Fragment);

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

    // texture1
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    int width, height, channels;
    char const * fileName = "../../Glitter/Media/Images/container.jpg";
    unsigned char *data = stbi_load(fileName, &width, &height, &channels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,  GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "load texel error" << std::endl;
    }

    // texture2
    GLuint  texture2;
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    char const * fileName2 = "../../Glitter/Media/Images/awesomeface.png";
    unsigned char *data2 = stbi_load(fileName2, &width, &height, &channels, 0);
    if (data2) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,  GL_UNSIGNED_BYTE, data2);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "load texel2 error" << std::endl;
    }

    shaderMgr.useProgram();
    glUniform1i(glGetUniformLocation(shaderMgr.getProgram(), "inputImageTexture"), 0);
    glUniform1i(glGetUniformLocation(shaderMgr.getProgram(), "inputImageTexture2"), 1);

    // 先旋转，再缩放
    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
    trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));
    GLuint transformLoc = glGetUniformLocation(shaderMgr.getProgram(), "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));


    // Rendering Loop
    while (glfwWindowShouldClose(mWindow) == false) {
        if (glfwGetKey(mWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(mWindow, true);

        // Background Fill Color
        glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Render
        shaderMgr.useProgram();

        // 每次渲染重新生成旋转矩阵，注释调这里会很奇妙
        glm::mat4 trans = glm::mat4(1.0f);
        trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f)); // switch the order
        trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0, 0.0, 1.0)); // switch the order

        GLuint transformLoc = glGetUniformLocation(shaderMgr.getProgram(), "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


        // second transformation
        // ---------------------
        trans = glm::mat4(1.0f); // reset it to identity matrix
        trans = glm::translate(trans, glm::vec3(-0.5f, 0.5f, 0.0f));
        float scaleAmount = sin(glfwGetTime());
        if (scaleAmount < 1e-6) {
            scaleAmount = -scaleAmount;
        }
        trans = glm::scale(trans, glm::vec3(scaleAmount, scaleAmount, scaleAmount));
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, &trans[0][0]); // this time take the matrix value array's first element as its memory pointer value

        // now with the uniform matrix being replaced with new transformations, draw it again.
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

