#pragma once
#define VAO_H

#include "VBO.h"

class VAO
{
public:
	GLuint id;
	VAO()
	{
		glGenVertexArrays(1, &id);
	}

	void bindVao()
	{
		glBindVertexArray(id);
	}

	void linkAttrib(VBO& vbo, GLuint layout, GLuint components, GLenum type, GLsizeiptr stride, void* offset)
	{
		vbo.bindVbo();
		glVertexAttribPointer(layout, components, type, GL_FALSE, stride, offset);
		glEnableVertexAttribArray(layout);
		vbo.unbindVbo();
	}

	void unbindVao()
	{
		glBindVertexArray(0);
	}

	void deleteVao()
	{
		glDeleteVertexArrays(1, &id);
	}

	~VAO()
	{
		deleteVao();
	}
};