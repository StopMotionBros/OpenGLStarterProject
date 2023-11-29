#include "VertexBuffer.h"
#include "Renderer.h"

VertexBuffer::VertexBuffer(const void* data, uint size, int usage)
{
    GLCall(glGenBuffers(1, &m_RendererId));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererId));
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, usage));
}

VertexBuffer::~VertexBuffer()
{
    GLCall(glDeleteBuffers(1, &m_RendererId));
}

void VertexBuffer::SetData(const void* data, uint size)
{
    Bind();
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

void VertexBuffer::Bind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererId));
}

void VertexBuffer::Unbind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
