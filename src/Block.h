#pragma once
#include <iostream>
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"

struct blockVertex
{
    glm::vec3 position;
    glm::vec3 color;
    glm::vec2 txCoord;
};


class Block
{
public:
    glm::vec3 position;
    glm::vec3 size;
    glm::vec3 color;
    glm::vec2 textureNum = glm::vec2(0.0f);

    std::array<blockVertex, 24> createBlock();


private:

};

