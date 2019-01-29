//
// Created by HFY on 2019/1/29.
//

#ifndef GLITTER_HELLOTRIANGLEIBO_H
#define GLITTER_HELLOTRIANGLEIBO_H


class HelloTriangleIBO {
public:
    /* Rectangle */
    int runHelloTriangleIBO();

private:
    enum LogType {
        Shader = 0,
        Program = 1,
    };
    void checkStatus(unsigned int handler, LogType type);
};


#endif //GLITTER_HELLOTRIANGLEIBO_H
