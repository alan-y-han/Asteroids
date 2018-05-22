#pragma once

#include <glad\glad.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include <glm\glm.hpp>


class Shader
{
public:
    Shader(std::string vertexPath, std::string fragmentPath);
    ~Shader();

    void use(); // use/activate the shader

    // functions for setting uniforms
    void setViewMatrix(const glm::mat4& mat);
    void setProjectionMatrix(const glm::mat4& mat);


    unsigned int ID; // program ID


private:
    std::string readShaderFile(std::string& filepath);
    unsigned int compileShader(int shaderType, const char* shaderCode, std::string debugName);
    void checkCompileErrors(GLuint shader, std::string type);


    GLint viewLocation;
    GLint projectionLocation;
};
