//#pragma once
//#define CUBE_H
//
//#define PI 3.1415926535897932384626433832795
//
//#define TINYOBJLOADER_IMPLEMENTATION
//
//#include "Shader.h"
//#include "Texture.h"
//
//#include "Camera.h"
//
//#include <tinyobjloader/tiny_obj_loader.h>
//
//#include <math.h>
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//#include "MeshDataLoader.h"
//
//
//class Cube
//{
//private:
//	void setupCube()
//	{
//        verticesData = MeshDataLoader::loadObj("3dmodels/donut.obj");
//
//
//        myShader = new Shader("cubemaps.vs", "cubemaps.fs");
//
//        myTexture = new Texture("container.jpg");
//
//        glGenBuffers(1, &VBO);
//
//       // glGenBuffers(1, &EBO);
//
//        glGenVertexArrays(1, &VAO);
//
//        glBindVertexArray(VAO);
//        glBindBuffer(GL_ARRAY_BUFFER, VBO);
//        glBufferData(GL_ARRAY_BUFFER, verticesData.size() * sizeof(Vertex), verticesData.data(), GL_STATIC_DRAW);
//
//       
//
//        glEnableVertexAttribArray(0);
//        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
//        glEnableVertexAttribArray(1);
//        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texCoord));
//	}
//
//   
//
//public:
//	GLuint VAO;
//	GLuint VBO;
//    GLuint EBO;
//	Shader* myShader;
//	Texture* myTexture;
//    std::vector<Vertex> verticesData;
//    std::vector<unsigned int> indicesData;
//
//	Cube() 
//	{
//        setupCube();
//	}
//
//	~Cube()
//    {
//		delete myShader;
//		glDeleteBuffers(1, &VBO);
//		glDeleteVertexArrays(1, &VAO);
//	}
//
//    void renderCube(double deltaTime, Camera* cam, glm::mat4* view, glm::mat4 projection)
//    {
//        myShader->use();
//        glm::mat4 model = glm::mat4(1.0f);
//        model = glm::translate(model, glm::vec3(-0.5f, 0.0f, 0.0f));
//        //model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
//        //model = glm::rotate(model, (float)glfwGetTime() * (float) PI / 2, glm::vec3(0.0f, 1.0f, 0.0f));
//        *view = cam->getViewMatrix();
//        myShader->setMat4("model", model);
//        myShader->setMat4("projection", projection);
//        myShader->setMat4("view", *view);
//        glBindVertexArray(VAO);
//        glActiveTexture(GL_TEXTURE0);
//        glBindTexture(GL_TEXTURE_2D, myTexture->handle);
//        glDrawArrays(GL_TRIANGLES, 0, verticesData.size());
//        //glDrawElements(GL_TRIANGLES, indicesData.size(), GL_UNSIGNED_INT, 0);
//        glBindVertexArray(0);
//    }
//
//};