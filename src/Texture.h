#pragma once

#include "Renderer.h"
#include <string>

class Texture
{
public:
	Texture(std::string path);
	~Texture();

	void Bind(uint slot = 0) const;
	void Unbind() const;

	inline int GetWidth() { return m_Width; }
	inline int GetHeight() { return m_Height; }

	inline uint GetID() const { return m_RendererId; }
private:
	uint m_RendererId;
	std::string m_FilePath;
	ubyte* m_LocalBuffer;
	int m_Width, m_Height, m_BPP;
};