#include "Shader.h"

#include "GL/glew.h"

#include "Renderer.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

Shader::Shader(const std::string& filePath)
	: m_FilePath(filePath), m_RendererId(0)
{
    ShaderProgramSource source = ParseShader(filePath);
    m_RendererId = CreateShader(source.VertexSource, source.FragmentSource);
}

Shader::~Shader()
{
    GLCall(glDeleteProgram(m_RendererId));
}

ShaderProgramSource Shader::ParseShader(const std::string& filePath)
{
    std::ifstream stream(filePath);

    enum class ShaderType
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::stringstream ss[2];
    std::string line;
    ShaderType type = ShaderType::NONE;
    while (getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
                type = ShaderType::VERTEX;
            else if (line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;
        }
        else
        {
            ss[(int)type] << line << '\n';
        }
    }

    return {ss[0].str(), ss[1].str()};
}

uint Shader::CompileShader(uint type,const std::string& source)
{
    uint id = glCreateShader(type);
    const char* src = source.c_str();
    GLCall(glShaderSource(id, 1, &src, nullptr));
    GLCall(glCompileShader(id));

    int result;
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
    if (result == GL_FALSE)
    {
        int length;
        GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex " : "fragment ") << "shader." << std::endl;
        std::cout << "\t" << message << std::endl;

        GLCall(glDeleteShader(id));
        return 0;
    }

    return id;
}

uint Shader::CreateShader(const std::string& vertex, const std::string& fragment)
{
    uint program = glCreateProgram();
    uint vs = CompileShader(GL_VERTEX_SHADER, vertex);
    uint fs = CompileShader(GL_FRAGMENT_SHADER, fragment);

    GLCall(glAttachShader(program, vs));
    GLCall(glAttachShader(program, fs));
    GLCall(glLinkProgram(program));
    GLCall(glValidateProgram(program));

    GLCall(glDeleteShader(vs));
    GLCall(glDeleteShader(fs));

    return program;
}

void Shader::Bind() const
{
    GLCall(glUseProgram(m_RendererId));
}

void Shader::Unbind() const
{
    GLCall(glUseProgram(0));
}

void Shader::SetUniform1i(const std::string& name, int v)
{
    GLCall(glUniform1i(GetUniformLocation(name), v));
}

void Shader::SetUniform4f(const std::string& name, float x, float y, float z, float w)
{
    GLCall(glUniform4f(GetUniformLocation(name), x, y, z, w));
}

void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix)
{
    GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}

int Shader::GetUniformLocation(const std::string& name)
{
    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
        return m_UniformLocationCache[name];

    GLCall(int loc = glGetUniformLocation(m_RendererId, name.c_str()));

    m_UniformLocationCache[name] = loc;
    return loc;
}

