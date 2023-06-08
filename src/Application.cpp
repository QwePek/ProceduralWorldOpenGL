#include "GL/glew.h"
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <array>
#include "Shader.h"
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"

#include "Camera.h"
#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"
#include "Block.h"

glm::vec2 windowSize = glm::vec2(1000, 800);

Camera cam(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f);
bool firstMouse = true;
float lastX = windowSize.x / 2.0f;
float lastY = windowSize.y / 2.0f;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    std::cout << "Chuj";
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cam.processInput(direction::FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cam.processInput(direction::BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cam.processInput(direction::LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cam.processInput(direction::RIGHT, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void mouse_callback(GLFWwindow* window, double xPos, double yPos)
{
    float xp = static_cast<float>(xPos);
    float yp = static_cast<float>(yPos);

    if (firstMouse)
    {
        lastX = xp;
        lastY = yp;
        firstMouse = false;
    }

    float xoffset = xp - lastX;
    float yoffset = lastY - yp; // reversed since y-coordinates go from bottom to top

    lastX = xp;
    lastY = yp;

    cam.processMouse(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xOffset, double yOffset)
{
    cam.processZoom(xOffset, yOffset);
}

int main(void)
{
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(windowSize.x, windowSize.y, "Minecraft", NULL, NULL);

    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;

        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    //Initializing GLEW
    if (glewInit() != GLEW_OK)
        std::cout << "Error initializing GLEW" << std::endl;

    std::cout << glGetString(GL_VERSION) << std::endl;


    glViewport(0, 0, windowSize.x, windowSize.y);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    
    {
        glEnable(GL_DEPTH_TEST); //Aby kurwa trojkaty sie rysowaly nie za sob¹ i nie nachodzily xd



        Block bloczek;
        bloczek.position = glm::vec3(0.0f, 0.0f, 0.0f);
        bloczek.size = glm::vec3(1.0f, 1.0f, 1.0f);
        bloczek.color = glm::vec3(1.0f, 1.0f, 1.0f);


        uint32_t indicies[] = {
            //0
            0,1,2, 2,1,3,
            //4
            4,5,6, 6,5,7,
            //8
            8,9,10, 9,10,11,
            //12
            12,13,14, 13,14,15,
            //16
            16,17,18, 17,18,19,
            //20
            20,21,22, 21,22,23,
        };


        //Creating, Compiling, Linking Shaders
        Shader myShader("src/Shaders/shader.shader");

        VertexBuffer vbo(sizeof(blockVertex) * 24 * 50); //VertexBuffer bedzie mogl przechowac 50 blokow
        //VertexBuffer vbo(squareMuj, sizeof(squareMuj)); //VertexBuffer bedzie mogl przechowac 50 blokow

        VertexArray vao;
        IndexBuffer ib(indicies, 36);

        VertexBufferLayout layout;
        layout.Push<float>(3);
        layout.Push<float>(3);
        layout.Push<float>(2);

        vao.addBuffer(vbo, layout);

        myShader.unbind();
        vbo.unbind();
        vao.unbind();
        ib.unbind();

        Texture tx1("res\\container.jpg");
        Texture tx2("res\\Textures\\AllTextures.png");

        //Hide mouse cursor
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        //Set mouse function callback
        glfwSetCursorPosCallback(window, mouse_callback);

        //Set scroll function callback
        glfwSetScrollCallback(window, scroll_callback);

        int mapWidth = 1, mapDepth = 1, maxHeight = 1;
        srand(time(NULL));
        std::vector<glm::vec3> pozycjeSzesc;
        for (int z = 0; z < mapDepth; z++)
        {
            for (int x = 0; x < mapWidth; x++)
            {
                float yHeight = rand() % maxHeight;
                for (int y = yHeight; y >= 0; y--)
                    pozycjeSzesc.push_back(glm::vec3(x /2.0f, y /2.0f, z /2.0f));
            }
        }

        Renderer renderer;

        while (!glfwWindowShouldClose(window))
        {
            float currFrame = static_cast<float>(glfwGetTime());
            deltaTime = currFrame - lastFrame;
            lastFrame = currFrame;

            renderer.clear();

            processInput(window);
            myShader.bind();

            //float squareMuj[] = {
            //    //Przednia 1: z-const
            //    -0.5f, -0.5f, -0.5f,   1.0f,1.0f,1.0f,  0.0f,0.0f,
            //    -0.5f,  0.5f, -0.5f,   1.0f,1.0f,1.0f,  0.0f,1.0f,
            //     0.5f, -0.5f, -0.5f,   1.0f,1.0f,1.0f,  1.0f,0.0f,
            //     0.5f,  0.5f, -0.5f,   1.0f,1.0f,1.0f,  1.0f,1.0f,

            //     //Sciana 2: z-const
            //     -0.5f, -0.5f, 0.5f,   1.0f,1.0f,1.0f,  0.0f,0.0f,
            //     -0.5f,  0.5f, 0.5f,   1.0f,1.0f,1.0f,  0.0f,1.0f,
            //      0.5f, -0.5f, 0.5f,   1.0f,1.0f,1.0f,  1.0f,0.0f,
            //      0.5f,  0.5f, 0.5f,   1.0f,1.0f,1.0f,  1.0f,1.0f,

            //      //Sciana 3: x-const
            //     -0.5f, -0.5f, -0.5f,   1.0f,1.0f,1.0f,  0.0f,0.0f,
            //     -0.5f,  0.5f, -0.5f,   1.0f,1.0f,1.0f,  0.0f,1.0f,
            //     -0.5f, -0.5f,  0.5f,   1.0f,1.0f,1.0f,  1.0f,0.0f,
            //     -0.5f,  0.5f,  0.5f,   1.0f,1.0f,1.0f,  1.0f,1.0f,

            //     //Sciana 4: x-const
            //     0.5f, -0.5f, -0.5f,   1.0f,1.0f,1.0f,  0.0f,0.0f,
            //     0.5f,  0.5f, -0.5f,   1.0f,1.0f,1.0f,  0.0f,1.0f,
            //     0.5f, -0.5f,  0.5f,   1.0f,1.0f,1.0f,  1.0f,0.0f,
            //     0.5f,  0.5f,  0.5f,   1.0f,1.0f,1.0f,  1.0f,1.0f,

            //     //Sciana 3: y-const
            //    -0.5f, -0.5f, -0.5f,   1.0f,1.0f,1.0f,  0.0f,0.0f,
            //    -0.5f, -0.5f,  0.5f,   1.0f,1.0f,1.0f,  0.0f,1.0f,
            //     0.5f, -0.5f, -0.5f,   1.0f,1.0f,1.0f,  1.0f,0.0f,
            //     0.5f, -0.5f,  0.5f,   1.0f,1.0f,1.0f,  1.0f,1.0f,

            //     //Sciana 4: y-const
            //    -0.5f,  0.5f, -0.5f,   1.0f,1.0f,1.0f,  0.0f,0.0f,
            //    -0.5f,  0.5f,  0.5f,   1.0f,1.0f,1.0f,  0.0f,1.0f,
            //     0.5f,  0.5f, -0.5f,   1.0f,1.0f,1.0f,  1.0f,0.0f,
            //     0.5f,  0.5f,  0.5f,   1.0f,1.0f,1.0f,  1.0f,1.0f
            //};


            auto b0 = bloczek.createBlock();

            blockVertex blok[24];
            memcpy(blok, b0.data(), b0.size() * sizeof(blockVertex));

            //for (int i = 0; i < 24; i++)
            //{
            //    if (i % 4 == 0)
            //        std::cout << std::endl;
            //    std::cout << i << ": " << blok[i].position.x << ", " << blok[i].position.y << ", " <<
            //        blok[i].position.z << ", " << blok[i].color.x << ", " << blok[i].color.y <<
            //        ", " << blok[i].color.z << ", " << blok[i].txCoord.x << ", " <<
            //        blok[i].txCoord.y << "   -   " << (sizeof(blockVertex) * i) << std::endl;

            //}
            //std::cin.get();

            vbo.updateData(blok, sizeof(blok));

            bloczek.position = glm::vec3(sin(glfwGetTime()), cos(glfwGetTime()), 0.0f);


            tx1.bind();
            tx2.bind(1);

            myShader.setUnfiformMat4f("projection", cam.getProjectionMatrix(windowSize));
            myShader.setUnfiformMat4f("view", cam.getViewMatrix());

            glm::mat4 modelMat = glm::mat4(1.0f);
            modelMat = glm::translate(modelMat, pozycjeSzesc[0]);
            modelMat = glm::rotate(modelMat, 0.0f, glm::vec3(0.5f, 1.0f, 0.0f));
            modelMat = glm::scale(modelMat, glm::vec3(0.5f, 0.5f, 0.5f));
            myShader.setUniform1i("ourTexture1", 0);
            myShader.setUnfiformMat4f("model", modelMat);

            renderer.draw(vao, ib, myShader);

            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }
    glfwTerminate();
    return 0;
}