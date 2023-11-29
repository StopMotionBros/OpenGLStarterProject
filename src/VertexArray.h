#pragma once

#include "VertexBuffer.h"

#include "Definitions.h"

class VertexBufferLayout;

class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

	void Bind() const;
	void Unbind() const;

	inline uint GetID() const { return m_RendererId; }
private:
	uint m_RendererId;
};

