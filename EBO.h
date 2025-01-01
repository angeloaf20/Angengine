#pragma once
#define EBO_H

#include <vector>
#include <glad/glad.h>

#include "Vertex.h"

class EBO
{
public:
	GLuint id;

	EBO(std::vector<GLuint>& indices)
	{
		glGenBuffers(1, &id);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
	}

	~EBO()
	{
		deleteEbo();
	}

	void bindEbo()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
	}

	void unbindEbo()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void deleteEbo()
	{
		glDeleteBuffers(1, &id);
	}

};