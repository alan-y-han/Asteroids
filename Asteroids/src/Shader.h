#pragma once

#include <glad\glad.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include <glm\gtc\type_ptr.hpp>


class Shader
{
public:
    // the program ID
    unsigned int ID;

    Shader(); // call initialiseShader() before use
    Shader(std::string& vertexPath, std::string& fragmentPath);
    // initialise the shader (used with the default constructor)
    void initialiseShader(std::string& vertexPath, std::string& fragmentPath);
    // use/activate the shader
    void use();
    // set uniforms
    void setModelMatrix(const glm::mat4& mat);
    void setViewMatrix(const glm::mat4& mat);
    void setProjectionMatrix(const glm::mat4& mat);
private:
    std::string readShaderFile(std::string& filepath);
    unsigned int compileShader(int shaderType, const char* shaderCode, std::string debugName);
    void checkCompileErrors(GLuint shader, std::string type);

    GLint modelLocation;
    GLint viewLocation;
    GLint projectionLocation;
};
