#pragma once

#include "GL/glew.h"
#include "Renderer.h"

#include <vector>
#include <stdexcept>

#include "Definitions.h"

struct VertexBufferElement
{
	uint type;
	uint count;
	ubyte normalized;

	static uint GetSizeOfType(uint type)
	{
		switch (type)
		{
		case GL_FLOAT: return sizeof(float);
		case GL_UNSIGNED_INT: return sizeof(uint);
		case GL_UNSIGNED_BYTE: return sizeof(ubyte);
		}
		ASSERT(false);
		return 0;
	}
};

class VertexBufferLayout
{
public:
	VertexBufferLayout()
		: m_Stride(0){}

	template<typename T>
	void Push(uint count)
	{
		std::runtime_error(false);
	}

	template<>
	void Push<float>(uint count)
	{
		m_Elements.push_back(VertexBufferElement{GL_FLOAT, count, GL_FALSE});
		m_Stride += sizeof(float) * count;
	}

	template<>
	void Push<uint>(uint count)
	{
		m_Elements.push_back(VertexBufferElement{GL_UNSIGNED_INT, count, GL_FALSE});
		m_Stride += sizeof(uint) * count;
	}

	template<>
	void Push<ubyte>(uint count)
	{
		m_Elements.push_back(VertexBufferElement{GL_UNSIGNED_BYTE, count, GL_TRUE});
		m_Stride += sizeof(ubyte) * count;
	}

	inline const std::vector<VertexBufferElement> GetElements() const { return m_Elements; }
	inline uint GetStride() const { return m_Stride; }

private:
	std::vector<VertexBufferElement> m_Elements;
	uint m_Stride;
};