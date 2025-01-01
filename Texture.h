#pragma once
#define STB_IMAGE_IMPLEMENTATION
#define TEXTURE_H

#include <glad/glad.h>
#include <stb/stb_image.h>


class Texture
{
public:
	GLuint handle;
	std::string type;
	std::string path;

	Texture(std::string& texPath, std::string& texType)
	{
		type = texType;
		path = texPath;
		int width, height, nrChannels;

		glGenTextures(1, &handle);

		//stbi_set_flip_vertically_on_load(true);
		unsigned char* textureImg = stbi_load(texPath.c_str(), &width, &height, &nrChannels, 0);

		if (textureImg)
		{
			GLenum format;
			if (nrChannels == 1)
				format = GL_RED;
			else if (nrChannels == 3)
				format = GL_RGB;
			else if (nrChannels == 4)
				format = GL_RGBA;

			glBindTexture(GL_TEXTURE_2D, handle);
			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, textureImg);
			glGenerateMipmap(GL_TEXTURE_2D);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			std::cout << texPath << " loaded" << std::endl;
		}
		else
		{
			std::cout << "Failed to load texture" << std::endl;
		}
		//stbi_set_flip_vertically_on_load(false);
		stbi_image_free(textureImg);

	}

	void use()
	{
		glBindTexture(GL_TEXTURE_2D, handle);
	}
};
