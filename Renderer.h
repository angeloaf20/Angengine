#pragma once
#define RENDERER_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <string>
#include "Constants.h"
#include "Shader.h"
#include "Texture.h"
#include "Skybox.h"
#include "Model.h"
#include "Cube.h"

class Renderer
{
public:

	Renderer() 
	{
        setupScene();
	}

	~Renderer() 
	{
        delete ChaoGarden;
        delete mySkybox;
	}

    void setupScene(void)
    {
        mainShader = new Shader("cubemaps.vert", "cubemaps.frag");
        
       // lightShader = new Shader("lightCube.vert", "lightCube.frag");
     
        ChaoGarden = new Model("3dmodels/ChaoGarden/Chao Garden.obj");

       // lightModel = new Model("3dmodels/Cube/cube.obj");

        Backpack = new Model("3dmodels/Backpack/backpack.obj");

        mySkybox = new Skybox(
            std::vector<std::string>
            {
                "skybox_images/valley_rt.jpg",
                "skybox_images/valley_lf.jpg",
                "skybox_images/valley_up.jpg",
                "skybox_images/valley_dn.jpg",
                "skybox_images/valley_ft.jpg",
                "skybox_images/valley_bk.jpg",
            }
        );
    }

    void drawScene(double deltaTime, Camera* cam)
    {
        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 view = cam->getViewMatrix();;
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), float(SCR_WIDTH) / float(SCR_HEIGHT), 0.1f, 100.0f);

        //glm::mat4 lightModelMat = glm::translate(glm::mat4(1.0f), glm::vec3(20.0f, 1.0f, 1.0f));
        //lightModelMat = glm::scale(lightModelMat, glm::vec3(0.05f));
        //lightShader->use();
        //lightShader->setVec3("objectColor", 1.0f, 0.5f, 0.31f);
        //lightShader->setVec3("lightColor", 1.0f, 1.0f, 1.0f);
        //lightShader->setVec3("lightPos", 1.2f, 1.0f, 2.0f);
        //lightShader->setVec3("viewPos", cam->Position);
        //lightShader->setMat4("model", lightModelMat);
        //lightShader->setMat4("view", view);
        //lightShader->setMat4("projection", projection);
        //lightModel->Draw(*lightShader);

        mainShader->use();
        //mainShader->setVec3("light.position", lightModelMat[0]);
        mainShader->setVec3("viewPos", cam->Position);
        mainShader->setVec3("light.diffuse", glm::vec3(1.0f, 0.3f, 0.7f));
        mainShader->setVec3("light.specular", glm::vec3(0.5f, 1.0f, 0.7f));
        mainShader->setVec3("light.ambient", glm::vec3(1.0f, 1.0f, 1.0f));

        glm::mat4 myMeshModel = glm::mat4(1.0f);
        myMeshModel = glm::scale(myMeshModel, glm::vec3(0.05f));
        myMeshModel = glm::translate(myMeshModel, glm::vec3(0.0f, 0.0f, 0.0f));

        mainShader->setMat4("model", myMeshModel);
        mainShader->setMat4("view", view);
        mainShader->setMat4("projection", projection);
        
        ChaoGarden->Draw(*mainShader);

        Backpack->Draw(*mainShader);

        glDepthFunc(GL_LEQUAL);
        mySkybox->renderSkybox(cam, &view, projection);
        glDepthFunc(GL_LESS);
    }

private:
    Model* ChaoGarden;
    Model* Backpack;
   // Model* lightModel;
    Skybox* mySkybox;
    Shader* mainShader;
    Shader* lightShader;
};