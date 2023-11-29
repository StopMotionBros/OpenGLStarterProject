#pragma once

#include "Definitions.h"

class IndexBuffer
{
public:
	IndexBuffer(const uint* data, uint count);
	~IndexBuffer();

	void SetData(const uint* data, uint count);

	void Bind() const;
	void Unbind() const;

	inline uint GetCount() const { return m_Count; }
private:
	uint m_RendererId;
	uint m_Count;
};