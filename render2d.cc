#include "render2d.h"
#include <cmath>
#include <valarray>

constexpr int NUM_EDGES = 30;

Render2D::Render2D(System* system, unsigned int width, unsigned int height) : system{system}, WIDTH{width}, HEIGHT{height}{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    unsigned int body = 0;
    while(body < system->getNumBodies()) {
        const unsigned int vertexOffset = body * (NUM_EDGES + 1);
        for (int i = 0; i < NUM_EDGES; i++) {
            indices.emplace_back(vertexOffset);
            indices.emplace_back(vertexOffset + i + 1);
            indices.emplace_back(vertexOffset + ((i + 1) % NUM_EDGES) + 1);
        }
        body += 1;
    }
}

Render2D::~Render2D() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void Render2D::update(const float dt) const {system->update(dt);}

void Render2D::render() const {
    std::vector<float> vertices;

    const std::vector<Body*> bodies = system->getBodies();
    for(const Body* body : bodies){
        std::vector<float> bodyVertices = getVertices(body);
        vertices.insert(vertices.end(), bodyVertices.begin(), bodyVertices.end());
    }

    const float* vertexData = vertices.data();
    const unsigned int* indexData = indices.data();

    // 1. bind Vertex Array Object
    glBindVertexArray(VAO);
    // 2. copy our vertices array in a vertex buffer for OpenGL to use
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertexData, GL_STATIC_DRAW);
    // 3. copy our index array in a element buffer for OpenGL to use
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indexData, GL_STATIC_DRAW);
    // 4. then set the vertex attributes pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Drawing
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
}

std::vector<float> Render2D::getVertices(const Body* body) const {
    std::vector<float> vertices;
    const Vector3 bodyPosition = body->getPosition();
    const float centerX = 2.0f * (bodyPosition.x / WIDTH) - 1.0f;
    const float centerY = 1.0f - 2.0f * (bodyPosition.y / HEIGHT);
    const float radius = body->getRadius();
    const Vector3 colour = body->getColour();
    const float red = colour.x / 255.0f;
    const float green = colour.y / 255.0f;
    const float blue = colour.z / 255.0f;

    vertices.emplace_back(centerX);
    vertices.emplace_back(centerY);
    vertices.emplace_back(0);
    vertices.emplace_back(red);
    vertices.emplace_back(green);
    vertices.emplace_back(blue);

    for(int i = 0; i < NUM_EDGES; i++) {
        const float angle = 2.0f * M_PI * i / NUM_EDGES;
        vertices.emplace_back(centerX + (radius / WIDTH * 2.0f) * std::cos(angle));
        vertices.emplace_back(centerY + (radius / HEIGHT * 2.0f) * std::sin(angle));
        vertices.emplace_back(0);
        vertices.emplace_back(red);
        vertices.emplace_back(green);
        vertices.emplace_back(blue);
    }
    return vertices;
}
