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

    // default constructor, doesn't initialise the shader
    Shader();
    // constructor reads and builds the shader
    Shader(std::string& vertexPath, std::string& fragmentPath);
    // initialise the shader (used with the default constructor)
    void initialiseShader(std::string& vertexPath, std::string& fragmentPath);
    // use/activate the shader
    void use();
    // utility uniform functions
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setVec2(const std::string& name, const glm::vec2& value) const;
    void setVec2(const std::string& name, float x, float y) const;
    void setVec3(const std::string& name, const glm::vec3& value) const;
    void setVec3(const std::string& name, float x, float y, float z) const;
    void setVec4(const std::string& name, const glm::vec4& value) const;
    void setVec4(const std::string& name, float x, float y, float z, float w) const;
    void setMat2(const std::string& name, const glm::mat2& mat) const;
    void setMat3(const std::string& name, const glm::mat3& mat) const;
    void setMat4(const std::string& name, const glm::mat4& mat) const;
private:
    std::string readShaderFile(std::string& filepath);
    unsigned int compileShader(int shaderType, const char* shaderCode, std::string debugName);
    void checkCompileErrors(GLuint shader, std::string type);
};
