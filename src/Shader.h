#pragma once
#include "Definitions.h"

#include <string>
#include <unordered_map>

#include "glm/glm.hpp"

struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader
{
public:
	Shader(const std::string& filePath);
	~Shader();

	void Bind() const;
	void Unbind() const;

	void SetUniform1i(const std::string& name, int v);
	void SetUniform4f(const std::string& name, float x, float y, float z, float w);
	void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);

	inline uint GetID() const { return m_RendererId; }

private:
	std::string m_FilePath;
	uint m_RendererId;
	std::unordered_map<std::string, int> m_UniformLocationCache;
	
	int GetUniformLocation(const std::string& name);

	ShaderProgramSource ParseShader(const std::string& filePath);
	uint CompileShader(uint type, const std::string& source);
	uint CreateShader(const std::string& vertex, const std::string& fragment);
};