#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>
#include "render2d.h"
#include "shader.h"
#include "surface.h"

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// Constants
constexpr int WINDOW_WIDTH = 2000;
constexpr int WINDOW_HEIGHT = 2000;
constexpr float PixelsToAU = 1000.0f;
constexpr float MToAU = 1.496e8f;

int main(){
    //------------------------------------------------------------------------------------------------------------------
    // GLFW Configurations
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // GLFW Window Creation
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Hello World", 0, 0);
    if(window == nullptr){
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // GLAD load OpenGL function pointers
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    //------------------------------------------------------------------------------------------------------------------
    // Shader

    Shader shader{"../shaders/vertex_shader_2d.vert", "../shaders/fragment_shader_2d.frag"};
    // constexpr float xOffset = 0.5f;
    // shader.setFloat("offset", xOffset);

    //------------------------------------------------------------------------------------------------------------------
    // Textures
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    constexpr int width = 256;
    constexpr int height = 256;
    const auto noiseData = new unsigned char[width * height * 3];
    fillSurfaceTexture(noiseData, width, height, 1);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, noiseData);
    glGenerateMipmap(GL_TEXTURE_2D);

    glActiveTexture(GL_TEXTURE0);
    delete[] noiseData;

    //------------------------------------------------------------------------------------------------------------------
    // Vertex Data
    System system;
    // system.addBody(
    //     1.989e36f, // Mass (kg)
    //     20, // Radius (m)
    //     Vector3(3 * WINDOW_WIDTH / 4.0f, WINDOW_HEIGHT / 2.0f, 0), // Position
    //     Vector3(0, 29.78e-1f, 0), // Velocity
    //     Vector3(0, 0, 0), // Acceleration
    //     Vector3(255, 255, 0) // Colour
    // );
    //
    // system.addBody(
    //     1.989e36f, // Mass (kg)
    //     20, // Radius (m)
    //     Vector3(WINDOW_WIDTH / 4.0f, WINDOW_HEIGHT / 2.0f, 0), // Position
    //     Vector3(0, -29.78e-1f, 0), // Velocity
    //     Vector3(0, 0, 0), // Acceleration
    //     Vector3(255, 0, 0) // Colour
    // );
    // Sun
    system.addBody(
        1.989e30f,
        25,
        {WINDOW_WIDTH / 2.0f,WINDOW_HEIGHT / 2.0f,0},
        {0, 0, 0},
        {0, 0, 0},
        {255,255,0},
        true
    );
    // Mercury
    // system.addBody(
    //     3.301e23f,
    //     10,
    //     {4 * WINDOW_WIDTH / 8.0f,2.44f * WINDOW_HEIGHT / 8.0f,0},
    //     {2.27526627016e-3, 0,0},
    //     {0, 0, 0},
    //     {169,169,169}
    // );
    // Venus
    // system.addBody(
    //     4.867e2f,
    //     10,
    //     {4 * WINDOW_WIDTH / 8.0f,6.88f * WINDOW_HEIGHT / 8.0f,0},
    //     {-0.0042f, 0, 0},
    //     {0, 0, 0},
    //     {255,198,73}
    // );
    // Earth
    system.addBody(
        5.97219e24f,
        5,
        {WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 4.0f,0},
        {0.023475f, 0, 0},
        {0, 0, 0},
        {0, 127, 255}
    );
    const Render2D render{&system, WINDOW_WIDTH, WINDOW_HEIGHT};

    // uncomment this call to draw in wireframe polygons.
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    //------------------------------------------------------------------------------------------------------------------
    // Main Loop
    float lastTime = glfwGetTime();
    while(!glfwWindowShouldClose(window)){
        // Calculate Delta Time
        const float currTime = glfwGetTime();
        const float dt = (currTime - lastTime);
        lastTime = currTime;

        // Input
        processInput(window);

        // Render
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();

        // Setting up Uniforms
        // const float timeValue = glfwGetTime();
        // const float greenValue = std::sin(timeValue) + 0.5f;
        // const int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
        // glUniform4f(vertexColorLocation, 1.0f, greenValue, 0.0f, 1.0f);

        // Actually Render
        render.update(1);
        render.render();

        // Check and call events and swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    //------------------------------------------------------------------------------------------------------------------
    // Cleaning up
    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, const int width, const int height) {glViewport(0, 0, width, height);}

void processInput(GLFWwindow* window){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);
}
