#pragma once

#include "Definitions.h"
#include "GL/glew.h"

class VertexBuffer
{
public:
	VertexBuffer(const void* data, uint size, int draw);
	~VertexBuffer();

	void SetData(const void* data, uint size);

	void Bind() const;
	void Unbind() const;

	inline uint GetID() const { return m_RendererId; }
private:
	uint m_RendererId;
};