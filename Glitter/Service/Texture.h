//
// Created by HFY on 2019/3/20.
//

#ifndef GLITTER_TEXTURE_H
#define GLITTER_TEXTURE_H

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <string>

class Texture {
public:
    static GLuint loadTexture(std::string path);
};


#endif //GLITTER_TEXTURE_H
