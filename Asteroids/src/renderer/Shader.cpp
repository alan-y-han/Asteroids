#include "Shader.h"


Shader::Shader(std::string vertexPath, std::string fragmentPath)
{
    // 1. retrieve the vertex/fragment source code from filepath
    std::string vShaderStr = readShaderFile(vertexPath).c_str();
    const char* vShaderCode = vShaderStr.c_str();
    std::string fShaderStr = readShaderFile(fragmentPath).c_str();
    const char* fShaderCode = fShaderStr.c_str();

    // 2. compile shaders
    unsigned int vertex = compileShader(GL_VERTEX_SHADER, vShaderCode, "VERTEX");
    unsigned int fragment = compileShader(GL_FRAGMENT_SHADER, fShaderCode, "FRAGMENT");

    // 3. create shader Program
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    // print linking errors if any
    checkCompileErrors(ID, "PROGRAM");

    // delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertex);
    glDeleteShader(fragment);

    // cache uniform locations
    viewLocation = glGetUniformLocation(ID, "view");
    projectionLocation = glGetUniformLocation(ID, "projection");
}

Shader::~Shader()
{
    glDeleteProgram(ID);
}

void Shader::use()
{
    glUseProgram(ID);
}

void Shader::setViewMatrix(const glm::mat4 & mat)
{
    glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &mat[0][0]);
}

void Shader::setProjectionMatrix(const glm::mat4 & mat)
{
    glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &mat[0][0]);
}

std::string Shader::readShaderFile(std::string& filePath)
{
    std::string shaderCode;
    std::ifstream shaderFile;
    // ensure ifstream object can throw exceptions:
    shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // open file
        shaderFile.open(filePath);
        std::stringstream vShaderStream;
        // read file's buffer contents into streams
        vShaderStream << shaderFile.rdbuf();
        // close file handlers
        shaderFile.close();
        // convert stream into string
        shaderCode = vShaderStream.str();
    }
    catch (std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE \"" << filePath << "\" NOT_SUCCESFULLY_READ" << std::endl;
    }
    return shaderCode;
}

unsigned int Shader::compileShader(int shaderType, const char* shaderCode, std::string debugName)
{
    unsigned int shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderCode, NULL);
    glCompileShader(shader);
    checkCompileErrors(shader, debugName);
    return shader;
}

void Shader::checkCompileErrors(GLuint shader, std::string type)
{
    GLint success;
    GLchar infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
}
