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

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "Camera.h"
#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"
#include "World.h"

glm::vec2 windowSize = glm::vec2(1000, 800);

Camera cam(glm::vec3(0.0f, 8.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, -45.0f);
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
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
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

    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
    {
        cam.turnOffMouseMovement();
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
    {
        cam.turnOnMouseMovement();
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }

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
    //std::cout << "Block size: " << sizeof(Block) << std::endl;

    glViewport(0, 0, windowSize.x, windowSize.y);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    
    {
        glEnable(GL_DEPTH_TEST); //Aby kurwa trojkaty sie rysowaly nie za sob¹ i nie nachodzily xd
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        srand(time(NULL));

        //Creating, Compiling, Linking Shaders
        Shader myShader("src/Shaders/shader.shader");

        VertexBuffer vbo(sizeof(blockVertex) * 24 * Chunk::getChunksMaxBlocks()); //VertexBuffer bedzie mogl przechowac 50 blokow

        VertexArray vao;

        VertexBufferLayout layout;
        layout.Push<float>(3);  //pos
        layout.Push<float>(2);  //tx coord

        vao.addBuffer(vbo, layout);

        myShader.unbind();
        vbo.unbind();
        vao.unbind();

        Texture tx1("res\\container.jpg");
        Texture tx2("res\\Textures\\AllTextures.png");

        //Hide mouse cursor
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        //Set mouse function callback
        glfwSetCursorPosCallback(window, mouse_callback);

        //Set scroll function callback
        glfwSetScrollCallback(window, scroll_callback);

        //ImGUI
        ImGui::CreateContext();

        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 330");

        ImGui::StyleColorsDark();
        //ImGui::StyleColorsLight();

        Renderer renderer;

        glm::vec2 worldSize = { 1,1 };
        World wrld(worldSize.x, worldSize.y);

        int seed = 123456;
        int ocataves = 8;
        float frequency = 0.01f;

        while (!glfwWindowShouldClose(window))
        {
            float currFrame = static_cast<float>(glfwGetTime());
            deltaTime = currFrame - lastFrame;
            lastFrame = currFrame;

            renderer.clear();

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            {
                ImGui::Begin("World generator");
                ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", deltaTime, 1 / deltaTime);

                ImGui::InputFloat2("World size", &worldSize.x, "%.0f", 1.0f);

                ImGui::InputInt("Seed", &seed);
                ImGui::SliderInt("Octaves", &ocataves, 1, 16);
                ImGui::SliderFloat("Frequency", &frequency, 0.0f, 1.0f);

                if (ImGui::Button("Generate world"))
                {
                    wrld.setFrequency(frequency);
                    wrld.setNumberOfOctaves(ocataves);
                    wrld.setWorldSeed(seed);

                    if (worldSize != wrld.getWorldSizeVec())
                        wrld.resizeWorld(worldSize);

                    wrld.updateAll();
                }

                ImGui::End();
            }

            processInput(window);

            for (int i = 0; i < wrld.getWorldSize(); i++)
            {
                std::vector<uint32_t> wrldIndicies = wrld.getIndicies(i);
                IndexBuffer ib(wrldIndicies.data(), wrldIndicies.size());

                std::vector<float> wrldGeometry = wrld.getGeometry(i);

                vbo.updateData(wrldGeometry.data(), wrldGeometry.size() * sizeof(float));
                ib.unbind();

                myShader.bind();

                tx1.bind();
                tx2.bind(1);

                myShader.setUnfiformMat4f("projection", cam.getProjectionMatrix(windowSize));
                myShader.setUnfiformMat4f("view", cam.getViewMatrix());

                glm::mat4 modelMat = glm::mat4(1.0f);
                
                modelMat = glm::translate(modelMat, wrld.getChunkPos(i) / 5.0f);
                modelMat = glm::rotate(modelMat, 0.0f, glm::vec3(0.5f, 1.0f, 0.0f));
                modelMat = glm::scale(modelMat, glm::vec3(0.2f, 0.2f, 0.2f));
                myShader.setUniform1i("ourTexture1", 1);
                myShader.setUnfiformMat4f("model", modelMat);

                renderer.draw(vao, ib, myShader);
            }
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}