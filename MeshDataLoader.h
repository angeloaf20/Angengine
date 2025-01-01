#pragma once
#define OBJLOADER_H

#include <glad/glad.h>

#include <assimp/scene.h>
#include <string>
#include <vector>
#include <iostream>

#include "VBO.h"
#include "VAO.h"

#include <unordered_map>
#include <fstream>
#include <sstream>

#include "Vertex.h"

struct MeshMaterial
{
	std::string name;
	GLuint id;
	float diffuse;
	float specular;
	float ambient;
	std::string map_Kd;
};

struct Face
{

};

struct NewMesh
{
	std::vector<Vertex> vertices;
	std::vector<std::string> texturePaths;
	std::vector<GLuint> indices;
	VAO* meshVao;
	glm::vec3 position;
	MeshMaterial material;
	float rotation;
	float scale;
	std::unordered_map<std::string, std::string> materialFileNames;
};


class MeshDataLoader
{
public:
	std::string currentMaterial;
	std::unordered_map<std::string, float> materialIndices;
	std::unordered_map<std::string, std::string> materialFileNames;

	NewMesh* createMesh(const char* objPath, const char* mtlPath)
	{
		resetVals();

		NewMesh* mesh = new NewMesh();

		loadMtl(mtlPath, *mesh);
		loadObj(objPath, *mesh);
		mesh->materialFileNames = materialFileNames;
		mesh->meshVao = new VAO();
		mesh->meshVao->bindVao();
		VBO meshVbo(mesh->vertices);
		mesh->meshVao->linkAttrib(meshVbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, position));
		mesh->meshVao->linkAttrib(meshVbo, 1, 2, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));
		mesh->meshVao->linkAttrib(meshVbo, 2, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, normal));
		mesh->meshVao->linkAttrib(meshVbo, 3, 1, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, textureLayer));

		mesh->meshVao->unbindVao();
		
		meshVbo.unbindVbo();

		return mesh;
	}

	void resetVals()
	{
		currentMaterial = "";
		materialIndices.clear();
		materialFileNames.clear();
	}

	void loadObj(const char* path, NewMesh& mesh)
	{
		//Vertex portions
		std::vector<glm::fvec3> vertexPositions;
		std::vector<glm::fvec2> vertexTexCoords;
		std::vector<glm::fvec3> vertexNormals;
		std::vector<std::string> vertexMaterials;

		//Face vectors
		std::vector<GLint> indicesPositions;
		std::vector<GLint> indicesTexCoords;
		std::vector<GLint> indicesNormals;
		std::vector<float> indicesLayers;

		//Vertex array
		std::vector<Vertex> vertices;

		std::cout << path << std::endl;


		std::stringstream ss;
		std::ifstream objFile(path);
		std::string line;
		std::string prefix;
		glm::vec3 vec3Buffer;
		glm::vec2 vec2Buffer;
		GLint bufferIndex = 0;
		int matInd = 0;

		//File open error check
		if (!objFile.is_open())
		{
			throw "ERROR::OBJLOADER::Could not open file.";
		}

		//Read one line at a time
		while (std::getline(objFile, line))
		{
			//Get the prefix of the line
			ss.clear();
			ss.str(line);
			ss >> prefix;

			if (prefix == "v") //Vertex position
			{
				ss >> vec3Buffer.x >> vec3Buffer.y >> vec3Buffer.z;
				vertexPositions.push_back(vec3Buffer);
			}
			else if (prefix == "vt")
			{
				ss >> vec2Buffer.x >> vec2Buffer.y;
				vertexTexCoords.push_back(vec2Buffer);
			}
			else if (prefix == "vn")
			{
				ss >> vec3Buffer.x >> vec3Buffer.y >> vec3Buffer.z;
				vertexNormals.push_back(vec3Buffer);
			}
			else if (prefix == "usemtl")
			{
				ss >> currentMaterial;
			}
			else if (prefix == "f")
			{
				char slash = '/';
				char space = ' ';

				int index = 0;

				while (ss >> bufferIndex)
				{
					if (index == 0)
						indicesPositions.push_back(bufferIndex);
					else if (index == 1)
						indicesTexCoords.push_back(bufferIndex);
					else if (index == 2)
						indicesNormals.push_back(bufferIndex);

					if (ss.peek() == slash)
					{
						++index;
						ss.ignore(1, slash);
					}
					else if (ss.peek() == space)
					{
						++index;
						ss.ignore(1, space);

					}

					if (index > 2)
						index = 0;
				}

				indicesLayers.push_back(materialIndices[currentMaterial]);
			}
		}
		objFile.close();

		//Build final vertex array (mesh)
		vertices.resize(indicesPositions.size(), Vertex());


		//Load in all indices
		for (size_t i = 0; i < vertices.size(); ++i)
		{
			Vertex vertex;
			vertex.position = vertexPositions[indicesPositions[i] - 1];
			vertex.texCoord = vertexTexCoords[indicesTexCoords[i] - 1];
			vertex.normal = vertexNormals[indicesNormals[i] - 1];
			vertex.textureLayer = indicesLayers[i / 3];

			mesh.vertices.push_back(vertex);
		}
		


		//DEBUG
		std::cout << "Nr of vertices: " << vertices.size() << "\n";

		//Loaded success
		std::cout << "OBJ file loaded!" << "\n";
	}

	void loadMtl(const char* path, NewMesh& mesh)
	{
		std::stringstream ss;
		std::ifstream mtlFile(path);
		std::string line;
		std::string prefix;
		std::string currWord;

		int index = 0;

		if (!mtlFile.is_open())
		{
			std::cout << "Could not open " << path << std::endl;
		}

		while (std::getline(mtlFile, line))
		{
			ss.clear();
			ss.str(line);
			ss >> prefix;

			if (prefix == "newmtl")
			{
				ss >> currentMaterial;
			}

			else if (prefix == "map_Kd")
			{
				ss >> currWord;
				materialFileNames[currentMaterial] = currWord;
				materialIndices[currentMaterial] = index;
				++index;
			}
		}
		mtlFile.close();

		std::cout << "Material files: " << std::endl;
		for (const auto& file : materialFileNames)
		{
			std::cout << file.first << ", " << file.second << std::endl;
		}

		createMaterial(mesh);
	}

	void createMaterial(NewMesh& mesh)
	{
		int width, height, nrChannels;
		std::vector<unsigned char*> imageData;

		for (const auto& file : materialFileNames) {
			stbi_set_flip_vertically_on_load(true);
			std::string path = "3dmodels/ChaoGarden/" + file.second;
			unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, STBI_rgb);
			if (data) {
				imageData.push_back(data);
			}
			else {
				std::cerr << "Failed to load texture: " << path << std::endl;
			}
		}


		// Allocate storage for the texture array
		glActiveTexture(GL_TEXTURE0);
		glGenTextures(1, &mesh.material.id);
		glBindTexture(GL_TEXTURE_2D_ARRAY, mesh.material.id);
		glTexStorage3D(GL_TEXTURE_2D_ARRAY, 1, GL_RGBA8, 256, 256, materialFileNames.size());

		// Load texture data into the texture array
		for (size_t i = 0; i < imageData.size(); ++i) 
		{
			glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, i+1, width, height, 1, GL_RGB, GL_UNSIGNED_BYTE, imageData[i]);
			free(imageData[i]); 
		}

		// Set texture parameters
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glBindTexture(GL_TEXTURE_2D_ARRAY, 0); // Unbind texture
	}
};