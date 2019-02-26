//
// Created by HFY on 2019/1/29.
//

#ifndef GLITTER_HELLOTRIANGLE_H
#define GLITTER_HELLOTRIANGLE_H


class HelloTriangle {
public:
    int runHelloTriangle();

private:
    enum LogType {
        Shader = 0,
        Program = 1,
    };
    void checkStatus(unsigned int handler, LogType type);
};


#endif //GLITTER_HELLOTRIANGLE_H
