#pragma once
#define ARRAY_TEXTURE

#include "Texture.h"

#include <vector>
#include <string>
#include <iostream>

class ArrayTexture
{
public:
	GLuint handle;

	ArrayTexture(GLsizei width, GLsizei height, GLsizei layers, std::vector<std::string> paths)
	{

		glGenTextures(1, &handle);
		glBindTexture(GL_TEXTURE_2D_ARRAY, handle);

		glTexStorage3D(GL_TEXTURE_2D_ARRAY, 1, GL_RGBA8, width, height, layers);

		// Set texture parameters
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT);

		// Load texture data for each layer
		for (int i = 0; i < layers; ++i) {
			int texWidth, texHeight, texChannels;
			std::string path = paths[i];
			const unsigned char* data = stbi_load(path.c_str(), &texWidth, &texHeight, &texChannels, 0);

			if (data) {
				glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, i, width, height, 1, GL_RGBA, GL_UNSIGNED_BYTE, data);
				stbi_image_free((void*)data);
			}
			else {
				std::cerr << "Failed to load texture: " << path << std::endl;
			}
		}
		glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
	}

	void use()
	{	
		glBindTexture(GL_TEXTURE_2D_ARRAY, handle);
	}

	~ArrayTexture()
	{
		glDeleteTextures(1, &handle);
	}
};