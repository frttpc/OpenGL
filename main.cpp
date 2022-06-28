#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "glm/glm.hpp"
#include "glm/gtc/constants.hpp"
#include "glm/gtx/rotate_vector.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/common.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Window.hpp"
#include "GameObj3D.hpp"
#include "ShaderProgram.hpp"
#include "Camera.hpp"
#include "parametric-3d/Parametric3DShape.hpp"
#include "CubeData.hpp"
#include "PlaneData.hpp"
#include "Textures.hpp"
#include "Keyboard.hpp"
#include "Mouse.hpp"
#include "Scene.hpp"
#include "Skybox.hpp"

#include "HUD.hpp"

//#include "ParticleShader.hpp"
//#include "Particle.hpp"

#include <iostream>
#include <vector>
using namespace std;

// Globals
int u_transform, u_pv, u_frame, u_light_pos, u_light_color, u_view_pos, u_p;
int collected = 0;


int main()
{
    // init window
    Window::init(1200, 1200, "my window");

    glfwSetInputMode(Window::window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetKeyCallback(Window::window, keyCallback);
    glfwSetCursorPosCallback(Window::window, cursorPositionCallback);
    glfwSetMouseButtonCallback(Window::window, mouse_button_callback);
    //glfwSetCursorEnterCallback(Window::window, cursor_enter_callback);

    // init objects
    Model3D sphereModel = Parametric3DShape::generate(ParametricLine::halfCircle, 50, 50);
    Model3D cubeModel1(CubeData::positions, CubeData::normals, CubeData::uvs_plane(75, 75), CubeData::indices);
    Model3D cubeModel2(CubeData::positions, CubeData::normals, CubeData::uvs_myFace(1, 1), CubeData::indices);
    Model3D cubeModel3(CubeData::positions, CubeData::normals, CubeData::uvs_chest(1, 1), CubeData::indices);
    Model3D cubeModel3_1(CubeData::positions, CubeData::normals, CubeData::uvs_chest(5, 5), CubeData::indices);
    Model3D cubeModel3_2(CubeData::positions, CubeData::normals, CubeData::uvs_chest(1, 5), CubeData::indices);

    glm::vec3 respawnPoint = glm::vec3(0.0, 10.0, 0.0);

    //  Player
    GameObj3D player(cubeModel2);
    player.translate(0, 10.0, 0.0);
    player.scale(0.3, 0.3, 0.3);
    player.textureId = 3;
    scene.push_back(&player);

    //  Coins
    vector<GameObj3D*> collectables;
    GameObj3D* coin1 = new GameObj3D(sphereModel);
    scene.push_back(coin1);
    coin1->translate(25, 5, 25.0);
    coin1->scale(0.3, 0.3, 0.1);
    coin1->hasGravity = false;
    coin1->isCollectable = true;
    collectables.push_back(coin1);

    GameObj3D* coin2 = new GameObj3D(sphereModel);
    scene.push_back(coin2);
    coin2->translate(31, 9, 25);
    coin2->scale(0.3, 0.3, 0.1);
    coin2->hasGravity = false;
    coin2->isCollectable = true;
    collectables.push_back(coin2);

    GameObj3D* coin3 = new GameObj3D(sphereModel);
    scene.push_back(coin3);
    coin3->translate(16, 0.2, -10);
    coin3->scale(0.3, 0.3, 0.1);
    coin3->hasGravity = false;
    coin3->isCollectable = true;
    collectables.push_back(coin3);

    GameObj3D* coin4 = new GameObj3D(sphereModel);
    scene.push_back(coin4);
    coin4->translate(-30, 0.2, -40);
    coin4->scale(0.3, 0.3, 0.1);
    coin4->hasGravity = false;
    coin4->isCollectable = true;
    collectables.push_back(coin4);

    GameObj3D* coin5 = new GameObj3D(sphereModel);
    //scene.push_back(coin5);
    coin5->translate(-40, 0.2, 50);
    coin5->scale(0.3, 0.3, 0.1);
    coin5->hasGravity = false;
    coin5->isCollectable = true;
    collectables.push_back(coin5);

    GameObj3D* coin6 = new GameObj3D(sphereModel);
    scene.push_back(coin5);
    coin6->translate(20, 0.2, 30);
    coin6->scale(0.3, 0.3, 0.1);
    coin6->hasGravity = false;
    coin6->isCollectable = true;
    collectables.push_back(coin6);

    GameObj3D* coin7 = new GameObj3D(sphereModel);
    scene.push_back(coin7);
    coin7->translate(-30, 0.2, 70);
    coin7->scale(0.3, 0.3, 0.1);
    coin7->hasGravity = false;
    coin7->isCollectable = true;
    collectables.push_back(coin7);

    GameObj3D* coin8 = new GameObj3D(sphereModel);
    scene.push_back(coin8);
    coin8->translate(-70, 0.2, 20);
    coin8->scale(0.3, 0.3, 0.1);
    coin8->hasGravity = false;
    coin8->isCollectable = true;
    collectables.push_back(coin8);

    GameObj3D* coin9 = new GameObj3D(sphereModel);
    scene.push_back(coin9);
    coin9->translate(-70, 0.2, -70);
    coin9->scale(0.3, 0.3, 0.1);
    coin9->hasGravity = false;
    coin9->isCollectable = true;
    collectables.push_back(coin9);

    GameObj3D* coin10 = new GameObj3D(sphereModel);
    scene.push_back(coin10);
    coin10->translate(80, 0.2, 80);
    coin10->scale(0.3, 0.3, 0.1);
    coin10->hasGravity = false;
    coin10->isCollectable = true;
    collectables.push_back(coin10);

    //  Plane
    GameObj3D* plane = new GameObj3D(cubeModel1);
    scene.push_back(plane);
    plane->translate(0, -1, 0);
    plane->scale(100, 0.5, 100);
    plane->textureId = 2;
    plane->hasGravity = false;
    plane->isCollectable = false;
    plane->isCollid = true;

    //  Cacti
    GameObj3D* cactus = new GameObj3D(cubeModel3_2);
    cactus->textureId = 8;
    cactus->translate(0, 1, 20.0);
    cactus->scale(0.3, 2, 0.3);
    scene.push_back(cactus);

    GameObj3D* cactus1 = new GameObj3D(cubeModel3_2);
    cactus1->textureId = 8;
    cactus1->translate(20, 1, 20.0);
    cactus1->scale(0.3, 1.5, 0.3);
    scene.push_back(cactus1);

    GameObj3D* cactus2 = new GameObj3D(cubeModel3_2);
    cactus2->textureId = 8;
    cactus2->translate(20, 1, 0.0);
    cactus2->scale(0.3, 1.5, 0.3);
    scene.push_back(cactus2);

    GameObj3D* cactus3 = new GameObj3D(cubeModel3_2);
    cactus3->textureId = 8;
    cactus3->translate(25, 1, 15.0);
    cactus3->scale(0.3, 2, 0.3);
    scene.push_back(cactus3);

    //  Wall
    GameObj3D* wall = new GameObj3D(cubeModel3_1);
    wall->translate(53.5, 10, 46.0);
    wall->scale(4, 4, 0.3);
    wall->textureId = 5;
    scene.push_back(wall);

    GameObj3D* wall2 = new GameObj3D(cubeModel3_1);
    wall2->translate(49, 10, 50.0);
    wall2->scale(0.3, 4, 4);
    wall2->textureId = 5;
    scene.push_back(wall2);

    GameObj3D* wall3 = new GameObj3D(cubeModel3_1);
    wall3->translate(58, 10, 50.0);
    wall3->scale(0.3, 4, 4);
    wall3->textureId = 5;
    scene.push_back(wall3);

    GameObj3D* wall4 = new GameObj3D(cubeModel3_1);
    wall4->translate(-24, 10, 60.0);
    wall4->scale(4, 4, 0.3);
    wall4->textureId = 5;
    scene.push_back(wall4);

    GameObj3D* wall5 = new GameObj3D(cubeModel3_1);
    wall5->translate(40, 10, -50.0);
    wall5->scale(0.3, 4, 4);
    wall5->textureId = 5;
    scene.push_back(wall5);

    GameObj3D* wall6 = new GameObj3D(cubeModel3_1);
    wall6->translate(75, 10, 75.0);
    wall6->scale(4, 4, 0.3);
    wall6->textureId = 5;
    scene.push_back(wall6);

    GameObj3D* wall7 = new GameObj3D(cubeModel3_1);
    wall7->translate(-65, 10, -65.0);
    wall7->scale(0.3, 4, 4);
    wall7->textureId = 5;
    scene.push_back(wall7);

    //  Steps
    GameObj3D* step = new GameObj3D(cubeModel3_1);
    step->translate(25, 4, 25.0);
    step->scale(4, 0.3, 4);
    step->textureId = 5;
    scene.push_back(step);
    step->hasGravity = false;

    GameObj3D* step2 = new GameObj3D(cubeModel3_1);
    step2->translate(31, 8, 25.0);
    step2->scale(4, 0.3, 4);
    step2->textureId = 5;
    scene.push_back(step2);
    step2->hasGravity = false;

    GameObj3D* step3 = new GameObj3D(cubeModel3_1);
    step3->translate(31, 12, 31.0);
    step3->scale(4, 0.3, 4);
    step3->textureId = 5;
    scene.push_back(step3);
    step3->hasGravity = false;

    //  Chest
    GameObj3D* chest = new GameObj3D(cubeModel3);
    chest->translate(31, 15, 31.0);
    chest->scale(0.8, 0.5, 0.5);
    chest->textureId = 1;
    scene.push_back(chest);
    chest->isCollectable = true;
    collectables.push_back(chest);

    GameObj3D* chest2 = new GameObj3D(cubeModel3);
    chest2->translate(53.5, 1, 50.0);
    chest2->scale(0.8, 0.5, 0.5);
    chest2->textureId = 1;
    scene.push_back(chest2);
    chest2->isCollectable = true;
    collectables.push_back(chest);
    
    //  Tree
    vector<GameObj3D*> tree;
    GameObj3D* leaves = new GameObj3D(sphereModel);
    leaves->scale(3, 3, 3);
    leaves->rotate(0, 180, 0);
    leaves->translate(-60, 7, 60);
    leaves->textureId = 4;
    leaves->hasGravity = false;
    tree.push_back(leaves);
    GameObj3D* body = new GameObj3D(cubeModel3_2);
    body->scale(0.5, 7, 0.5);
    body->translate(-60, 1, 60);
    body->textureId = 7;
    tree.push_back(body);

    scene.push_back(leaves);
    scene.push_back(body);

    //  Light
    glm::vec3 lightPos = glm::vec3(0.0, 10.0, 0.0);
    glm::vec3 lightColor = glm::vec3(1.0, 1.0, 1.0);

    // load textures
    const vector<string> texture_files{ "./textures/gold.jpg", "./textures/box.jpg", "./textures/plane_grass.jpg", "./textures/myFace.jpg", "./textures/leaves.jpg", "./textures/wall.jpg", "./textures/grass.jpg", "./textures/oak.jpg", "./textures/cactus.jpg" };
    vector<unsigned int> textures = Textures::loadTextures(texture_files);


    //  Load Particles
    
    //ParticleGenerator* Particles = new ParticleGenerator(100);

    


    // load skybox
    
    unsigned int skyboxVAO, skyboxVBO;
    initSkybox(skyboxVAO, skyboxVBO);
    vector<std::string> faces{
        "./textures/1.jpg",
        "./textures/awesomeface.jpg",
        "./textures/1.jpg",
        "./textures/4.jpg",
        "./textures/5.jpg",
        "./textures/5.jpg" };
    unsigned cubemapTexture = loadCubemap(faces);
    ShaderProgram skyboxShader("./shader/skybox.vert", "./shader/skybox.frag");
    auto skybox_texture = glGetUniformLocation(skyboxShader.id, "skybox");
    auto u_pv_sky = glGetUniformLocation(skyboxShader.id, "u_pv");
    glUniform1i(skybox_texture, 0); // 0th unit
    skyboxShader.use();
    


    // create shader
    ShaderProgram sp("./shader/vertex.vert", "./shader/frag.frag");
    sp.use();
    u_transform = glGetUniformLocation(sp.id, "u_transform");
    u_pv = glGetUniformLocation(sp.id, "u_pv");
    u_frame = glGetUniformLocation(sp.id, "u_frame");
    u_light_pos = glGetUniformLocation(sp.id, "u_light_pos");
    u_light_color = glGetUniformLocation(sp.id, "u_light_color");
    auto u_texture = glGetUniformLocation(sp.id, "u_texture");
    glUniform1i(u_texture, 0);
    glActiveTexture(GL_TEXTURE0); // active 0th unit

    unsigned a = 0;
    float oldTime = 0;
    float dT = 5;
    // game loop
    while (!Window::isClosed())
    {
        float oldmouseX = mouseX;

        //  deltaTime
        float time = glfwGetTime() * 1000;
        int deltaTime = (time - oldTime);
        oldTime = time;

        // update player and camera
        if (moveFront != 0) {
            player.moveFront(&player, moveFront * 0.05);
        }
        if (moveRight != 0)
        {
            player.rotate(player.rotation().x, player.rotation().y - moveRight * 0.4, player.rotation().z);
        }
        if (velocityY > 0) //&& landed)
        {
            player.moveUp(&player, velocityY * 0.001);
            velocityY -= velocityY * 0.05;
            //cout << velocityY << " " << player.position().y << endl;
            if (CollidesWithSth(player)) {
                player.moveUp(&player, velocityY * 0.01, true);
            }
        }
        else
            velocityY = 0;

        //cout << player.position().y << endl;

        Camera::position = player.position() - player.front() * 6.0f + player.up() * 3.0f;

        Camera::front = player.front() + glm::vec3(0, mouseY, 0);
        Camera::up = glm::cross(Camera::front, player.right());
        Camera::front = glm::rotateY(Camera::front, -mouseX);

        // update uniforms
        sp.use();
        glUniformMatrix4fv(u_pv, 1, GL_FALSE, glm::value_ptr(Camera::getProjMatrix() * Camera::getViewMatrix()));
        glUniform1i(u_frame, 1);
        glUniform3fv(u_light_pos, 1, glm::value_ptr(lightPos));
        glUniform3fv(u_light_color, 1, glm::value_ptr(lightColor));

        //  Collecting Collectables
        for (int i = 0; i < scene.size(); i++) {
            GameObj3D* object = scene[i];
            if (player.id != object->id) {
                if (intersect(player, *object)) {
                    if (object->isCollectable) 
                    {
                        cout << "2 __ " << "player collects: " << object->id << endl;
                        DeleteFromScene(scene, object->id);
                        collected++;
                    }   
                }
            }
        }

        // Drawing Particles
        //Particles->Update(dT, player, 2);

        if (player.position().y <= -10)
            player.position() = respawnPoint;


        // scene draw
        for (std::vector<GameObj3D*>::iterator t = scene.begin(); t != scene.end(); ++t)
        {
            // get the object
            const int i = t - scene.begin();

            // gravity logic
            GameObj3D* object = scene[i];
            if (object->hasGravity) //&& object->position().y > 0)
            {
                object->moveUp(object, -0.1);
                if (object->id == player.id && velocityY != 0)
                    object->moveUp(object, velocityY);
            }

            if (object->isCollectable)
            {
                object->rotate(0, object->rotation().y - 0.1, 0);
            }


            // for jump logic
            

            // draw the object
            glUniformMatrix4fv(u_transform, 1, GL_FALSE, glm::value_ptr(object->getTransform()));
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, textures[object->textureId]);
            object->draw();
            
            //drawHUD();
            //Particles->Draw(particlesp);
        }

        // draw skybox
        glDepthFunc(GL_LEQUAL); // change depth function so depth test passes when values are equal to depth buffer's content
        skyboxShader.use();
        glUniformMatrix4fv(u_pv_sky, 1, GL_FALSE, glm::value_ptr(Camera::getProjMatrix() * glm::mat4(glm::mat3(Camera::getViewMatrix()))));
        // skybox cube
        glBindVertexArray(skyboxVAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
        glDepthFunc(GL_LESS); // set depth function back to default
        

        // update the scene
        Window::refresh();

        if (collected == collectables.size() - 1) {
            Window::terminate();
            cout << "THANKS FOR PLAYING!!";
        }
            
    }

    Window::terminate();

    return 0;
}