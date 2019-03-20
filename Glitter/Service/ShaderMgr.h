//
// Created by HFY on 2019/1/31.
//

#ifndef GLITTER_SHADERMGR_H
#include "glad/glad.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <iostream>
#include <fstream>
#include <memory>

#define GLITTER_SHADERMGR_H


class ShaderMgr {
public:
    enum ShaderType {
        Vertex = 0,
        Fragment,
    };
public:
    ShaderMgr();
    ~ShaderMgr();

    void attach(std::string const shaderFile, ShaderType const shaderType);
    void attach(char const *shaderSource, ShaderType const shaderType);
    void useProgram();
    GLuint getProgram();
    GLint getUniformLocation(std::string const & name);

    // Wrap Calls to glUniform
    void bind(unsigned int location, float value);
    void bind(unsigned int location, glm::mat4 const & matrix);

    template<typename T> void bind(std::string const & name, T&& value)
    {
        int location = glGetUniformLocation(program_, name.c_str());
        if (location == -1) fprintf(stderr, "Missing Uniform: %s\n", name.c_str());
        else bind(location, std::forward<T>(value));
    }


private:
    GLuint program_;
};
#endif //GLITTER_SHADERMGR_H
