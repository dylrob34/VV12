#include "pch.h"
#include "Shader.h"

struct ShaderProgramSource
{
    std::string VertexSource;
    std::string FragmentSource;
};

ShaderProgramSource ParseShader(const std::string& filepath);

Shader::Shader(const std::string& filePath)
	: id(0), filePath(filePath)
{

    ShaderProgramSource source = ParseShader(filePath);
    id = CreateShader(source.VertexSource, source.FragmentSource);
    GLCall(glUseProgram(id));
}

Shader::~Shader()
{
    GLCall(glDeleteProgram(id));
}

ShaderProgramSource ParseShader(const std::string& filepath)
{
    std::ifstream stream(filepath);

    enum ShaderType
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
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
    return { ss[0].str(), ss[1].str() };
}

unsigned int Shader::CreateShader(const std::string& VertexShader, const std::string& FragmentShader)
{
    GLCall(unsigned int program = glCreateProgram());
    unsigned int vs = CompileShader(VertexShader, GL_VERTEX_SHADER);
    unsigned int fs = CompileShader(FragmentShader, GL_FRAGMENT_SHADER);

    GLCall(glAttachShader(program, vs));
    GLCall(glAttachShader(program, fs));
    GLCall(glLinkProgram(program));
    GLCall(glValidateProgram(program));

    GLCall(glDeleteShader(vs));
    GLCall(glDeleteShader(fs));

    return program;
}

unsigned int Shader::CompileShader(const std::string& source, unsigned int type)
{
    GLCall(unsigned int shader = glCreateShader(type));
    const char* src = source.c_str();
    GLCall(glShaderSource(shader, 1, &src, nullptr));
    GLCall(glCompileShader(shader));

    int result;
    GLCall(glGetShaderiv(shader, GL_COMPILE_STATUS, &result));
    if (result != GL_TRUE)
    {
        int length;
        GLCall(glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length));
        char* message = (char*)alloca(length * sizeof(char));
        GLCall(glGetShaderInfoLog(shader, length, &length, message));
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader" << std::endl;
        std::cout << message << std::endl;
    }

    return shader;

}

void Shader::Bind() const
{
    GLCall(glUseProgram(id));
}

void Shader::Unbind() const
{
    GLCall(glUseProgram(0));
}

int Shader::GetUniformLocation(const std::string& name)
{
    GLCall(return glGetUniformLocation(id, name.c_str()));
}
