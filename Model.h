#pragma once
#define MODEL_H

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.h"

class Model
{
private:
	void loadModel(std::string path)
	{
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_OptimizeMeshes | aiProcess_FlipUVs);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
			return;
		}
		directory = path.substr(0, path.find_last_of('/'));
		std::cout << "Reading from directory: " << directory << std::endl;
		processNode(scene->mRootNode, scene);
	}

	void processNode(aiNode *node, const aiScene *scene)
	{
		for (uint i = 0; i < node->mNumMeshes; ++i)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			meshes.push_back(processMesh(mesh, scene));
		}

		for (uint i = 0; i < node->mNumChildren; i++)
		{
			processNode(node->mChildren[i], scene);
		}
	}

	Mesh processMesh(aiMesh *mesh, const aiScene *scene)
	{
		std::vector<Vertex> vertices;
		std::vector<uint> indices;
		std::vector<Texture> textures;

		for (uint i = 0; i < mesh->mNumVertices; ++i)
		{
			Vertex vertex;
			glm::vec3 tempVec3;

			tempVec3.x = mesh->mVertices[i].x;
			tempVec3.y = mesh->mVertices[i].y;
			tempVec3.z = mesh->mVertices[i].z;
			vertex.Position = tempVec3;

			if (mesh->HasNormals())
			{
				tempVec3.x = mesh->mNormals->x;
				tempVec3.y = mesh->mNormals->y;
				tempVec3.z = mesh->mNormals->z;
				vertex.Normal = tempVec3;
			}
			
			if (mesh->mTextureCoords[0])
			{
				glm::vec2 tempVec2;
				tempVec2.x = mesh->mTextureCoords[0][i].x;
				tempVec2.y = mesh->mTextureCoords[0][i].y;
				vertex.TexCoords = tempVec2;

				/* For later
				tempVec3.x = mesh->mTangents[i].x;
				tempVec3.y = mesh->mTangents[i].y;
				tempVec3.z = mesh->mTangents[i].z;
				vertex.Tangent = tempVec3;
				// bitangent
				tempVec3.x = mesh->mBitangents[i].x;
				tempVec3.y = mesh->mBitangents[i].y;
				tempVec3.z = mesh->mBitangents[i].z;
				vertex.Bitangent = tempVec3;
				*/
			}
			else vertex.TexCoords = glm::vec2(0.0f, 0.0f);

			vertices.push_back(vertex);
		}

		for (uint i = 0; i < mesh->mNumFaces; ++i)
		{
			aiFace face = mesh->mFaces[i];

			for (uint j = 0; j < face.mNumIndices; ++j)
			{
				indices.push_back(face.mIndices[i]);
			}
		}

		if (mesh->mMaterialIndex >= 0)
		{
			aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

			std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
			textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

			std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
			textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

			
		}

		

		return Mesh(vertices, indices, textures);
	}

	std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName)
	{
		std::vector<Texture> textures;

		for (uint i = 0; i < mat->GetTextureCount(type); ++i)
		{
			aiString str;
			mat->GetTexture(type, i, &str);
			bool skip = false;

			for (uint j = 0; j < texturesLoaded.size(); ++j)
			{
				std::cout << texturesLoaded[j].path << std::endl;
				if (std::strcmp(texturesLoaded[j].path.data(), str.C_Str()) == 0)
				{
					textures.push_back(texturesLoaded[j]);
					skip = true;
					break;
				}
			}

			std::string texPath = directory + '/' + static_cast<std::string>(str.C_Str());
			Texture tex(texPath, typeName);
			textures.push_back(tex);
		}

		return textures;
	}

public:
	std::vector<Mesh> meshes;
	std::vector<Texture> texturesLoaded;
	std::string directory;

	Model(std::string const& path)
	{
		loadModel(path);
	}
	void Draw(Shader& shader)
	{
		for (uint i = 0; i < meshes.size(); ++i)
		{
			meshes[i].renderMesh(&shader);
		}
	}
};