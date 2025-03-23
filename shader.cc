#include "shader.h"

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath){
    // 1. Retrieve vertex/fragment source code from Paths
    std::string vertexCode;
    std::string fragmentCode;
    try{
        // Open files
        std::ifstream vShaderFile{vertexPath};
        std::ifstream fShaderFile{fragmentPath};
        // ensure ifstream objects can throw exceptions:
        vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        // Read file's buffer into string streams
        std::stringstream vShaderStream, fShaderStream;
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // Convert string stream to strings
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch(const std::exception &e){
        std::cerr << "Error: Failed to read shaders: " << e.what() << std::endl;
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    // 2. Compile Shaders
    unsigned int vertex, fragment;
    int success;
    char infoLog[512];

    // Vertex Shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, 0);
    glCompileShader(vertex);
    // vertex shader compile errors?
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(vertex, 512, 0, infoLog);
        std::cerr << "Error: Failed to compile vertex shader: " << infoLog << std::endl;
    }

    // Fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, 0);
    glCompileShader(fragment);
    // fragment shader compile errors?
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if(!success){
      glGetShaderInfoLog(fragment, 512, 0, infoLog);
      std::cerr << "Error: Failed to compile fragment shader: " << infoLog << std::endl;
    }

    // Shader Program
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    // program linking errors?
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if(!success){
        glGetProgramInfoLog(ID, 512, 0, infoLog);
        std::cerr << "Error: Failed to link program: " << infoLog << std::endl;
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::use() {glUseProgram(ID);}

// Uniform Setters
void Shader::setBool(const std::string& name, bool value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}
void Shader::setInt(const std::string& name, int value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}
void Shader::setFloat(const std::string &name, float value) const {
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}