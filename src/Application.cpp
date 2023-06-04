#include "GL/glew.h"
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include "Shader.h"
#include "stb_image\stb_image.h"
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"
#include "Camera.h"
#include "Renderer.h"

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

        float squareMuj[] = {
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
             0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
             0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
             0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

            -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
             0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
             0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
             0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

            -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

             0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
             0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
             0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
             0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
             0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
             0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
             0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
             0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
             0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,

            -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
             0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
             0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
             0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f
        };

        //uint32_t indicies[] = {
        //    0,1,3,
        //    1,2,3
        //};

        float texCoords[] = {
            0.0f, 0.0f,
            1.0f, 0.0f,
            1.0f, 1.0f,
            0.0f, 1.0f
        };

        //Creating, Compiling, Linking Shaders
        Shader myShader("src/Shaders/shader.shader");

        uint32_t vbo, vao, ebo;
        glGenVertexArrays(1, &vao);

        //glGenBuffers(1, &vbo);
        glGenBuffers(1, &ebo);

        glBindVertexArray(vao);
        //glBindBuffer(GL_ARRAY_BUFFER, vbo);
        //glBufferData(GL_ARRAY_BUFFER, sizeof(squareMuj), squareMuj, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);


        //Texturki
        uint32_t tex[2];
        glGenTextures(2, tex);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, tex[0]);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_set_flip_vertically_on_load(true);

        int width, height, nrChannels;
        unsigned char* imgData = stbi_load("res\\container.jpg", &width, &height, &nrChannels, 0);

        if (imgData)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imgData);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load image!" << std::endl;
        }
        stbi_image_free(imgData);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, tex[1]);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        imgData = stbi_load("res\\awesomeface.png", &width, &height, &nrChannels, 0);

        if (imgData)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imgData);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load image!" << std::endl;
        }
        stbi_image_free(imgData);

        myShader.bind();
        myShader.setUniform1i("ourTexture1", 0);
        myShader.setUniform1i("ourTexture2", 0);
        myShader.unbind();

        glBindTexture(GL_TEXTURE_2D, 0);

        //Hide mouse cursor
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        //Set mouse function callback
        glfwSetCursorPosCallback(window, mouse_callback);

        //Set scroll function callback
        glfwSetScrollCallback(window, scroll_callback);

        int mapWidth = 20, mapDepth = 20, maxHeight = 5;
        srand(time(NULL));
        std::vector<glm::vec3> pozycjeSzesc;
        for (int z = 0; z < mapDepth; z++)
        {
            for (int x = 0; x < mapWidth; x++)
            {
                float yHeight = rand() % maxHeight;
                for (int y = yHeight; y >= 0; y--)
                    pozycjeSzesc.push_back(glm::vec3(x, y, z));

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

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, tex[0]);
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, tex[1]);

            glBindVertexArray(vao);

            myShader.setUnfiformMat4f("projection", cam.getProjectionMatrix(windowSize));
            myShader.setUnfiformMat4f("view", cam.getViewMatrix());


            for (uint32_t i = 0; i < pozycjeSzesc.size(); i++)
            {
                glm::mat4 modelMat = glm::mat4(1.0f);
                modelMat = glm::translate(modelMat, pozycjeSzesc[i]);
                modelMat = glm::rotate(modelMat, 0.0f, glm::vec3(0.5f, 1.0f, 0.0f));

                if (i % 2 == 0)
                {
                    myShader.setUniform1i("ourTexture1", 0);

                }
                else
                {
                    myShader.setUniform1i("ourTexture1", 1);
                }
                myShader.setUnfiformMat4f("model", modelMat);

                glDrawArrays(GL_TRIANGLES, 0, 36);
            }


            //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

            glBindVertexArray(0);

            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        glDeleteVertexArrays(1, &vao);
        glDeleteBuffers(1, &vbo);
        glDeleteBuffers(1, &ebo);
    }
    glfwTerminate();
    return 0;
}