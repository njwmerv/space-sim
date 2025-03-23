#ifndef SHADER_H
#define SHADER_H
#include <fstream>
#include <glad/glad.h>
#include <iostream>
#include <sstream>
#include <string>

class Shader{
    unsigned int ID;

public:
    Shader(const std::string& vertexPath, const std::string& fragmentPath);

    void use();

    [[nodiscard]] unsigned int getID() const;

    // Uniform utilities
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
};

#endif //SHADER_H
