#pragma once

class VertexBuffer
{
private:
	unsigned int id;

public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;
};

class IndexBuffer
{
private:
	unsigned int id;
	unsigned int count;
public:
	IndexBuffer(const void* data, unsigned int count);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;

	inline unsigned int GetCount() { return count; }
};