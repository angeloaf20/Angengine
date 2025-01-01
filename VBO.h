#pragma once
#define VBO_H

#include <vector>
#include <glad/glad.h>

#include "Vertex.h"

class VBO
{
public:
	GLuint id;

	VBO(std::vector<Vertex>& vertices)
	{
		glGenBuffers(1, &id);
		glBindBuffer(GL_ARRAY_BUFFER, id);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
	}

	~VBO()
	{
		deleteVbo();
	}

	void bindVbo()
	{
		glBindBuffer(GL_ARRAY_BUFFER, id);
	}

	void unbindVbo()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void deleteVbo()
	{
		glDeleteBuffers(1, &id);
	}

};