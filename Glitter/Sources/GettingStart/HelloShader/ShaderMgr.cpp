//
// Created by HFY on 2019/1/31.
//

#include "ShaderMgr.h"

ShaderMgr::ShaderMgr() {
    program_ = glCreateProgram();
}

ShaderMgr::~ShaderMgr() {

}

void ShaderMgr::attach(std::string const shaderFile, const ShaderMgr::ShaderType shaderType) {

    std::ifstream fd(shaderFile);
    auto src = std::string(std::istreambuf_iterator<char>(fd),
                           (std::istreambuf_iterator<char>()));
    const char * source = src.c_str();

    // Create Shader
    unsigned int shader;
    if (shaderType == ShaderType::Vertex) {
        shader = glCreateShader(GL_VERTEX_SHADER);
    } else {
        shader = glCreateShader(GL_FRAGMENT_SHADER);
    }

    // Compile Shader
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    };

    // Attach with Program
    glAttachShader(program_, shader);
    glLinkProgram(program_);

    glGetProgramiv(program_, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(program_, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(shader);
}

void ShaderMgr::attach(char const *shaderSource, const ShaderMgr::ShaderType shaderType) {
    unsigned int shader;
    if (shaderType == ShaderType::Vertex) {
        shader = glCreateShader(GL_VERTEX_SHADER);
    } else {
        shader = glCreateShader(GL_FRAGMENT_SHADER);
    }

    // Compile Shader
    glShaderSource(shader, 1, &shaderSource, NULL);
    glCompileShader(shader);

    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    };

    // Attach with Program
    glAttachShader(program_, shader);
    glLinkProgram(program_);

    glGetProgramiv(program_, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(program_, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(shader);
}

void ShaderMgr::useProgram() {
    glUseProgram(program_);
}

GLuint ShaderMgr::getProgram(){ return program_; };

GLint ShaderMgr::getUniformLocation(std::string const &name) {
    GLint location = glGetAttribLocation(program_ ,name.c_str());
    return location;
}







