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
    Shader(); // call initialiseShader() before use
    Shader(std::string vertexPath, std::string fragmentPath);

    void initialiseShader(std::string vertexPath, std::string fragmentPath); // must call this after class construction
    void use(); // use/activate the shader

    // functions for setting uniforms
    void setModelMatrix(const glm::mat4& mat);
    void setViewMatrix(const glm::mat4& mat);
    void setProjectionMatrix(const glm::mat4& mat);
    void setAlpha(const float alpha);


    unsigned int ID; // program ID


private:
    std::string readShaderFile(std::string& filepath);
    unsigned int compileShader(int shaderType, const char* shaderCode, std::string debugName);
    void checkCompileErrors(GLuint shader, std::string type);


    GLint viewLocation;
    GLint projectionLocation;
};
