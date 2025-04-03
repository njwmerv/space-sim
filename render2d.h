#ifndef RENDER2D_H
#define RENDER2D_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "system.h"

class Render2D {
public:
    explicit Render2D(System* system, unsigned int width, unsigned int height);

    ~Render2D();

    void render() const;

    void update() const;

private:
    System* system;
    std::vector<unsigned int> indices;
    unsigned int WIDTH;
    unsigned int HEIGHT;
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;

    std::vector<float> getVertices(const Body* body) const ;
};

#endif //RENDER2D_H
