#pragma once
#include <iostream>
#include <vector>
#include <array>

#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"

#include "perlinNoise/PerlinNoise.hpp"

struct blockVertex
{
    glm::vec3 position;
    glm::vec3 color;
    glm::vec2 txCoord;
};

namespace BLOCK
{
    enum class SIDE { ALL, TOP, BOTTOM, SIDE1, SIDE2, SIDE3, SIDE4 };
}



//NA RAZIE TX 2,0 TO JEST AIR!!!
class Block
{
public:
    Block();
    Block(glm::vec3 pos, glm::vec3 size);
    Block(glm::vec3 pos, glm::vec3 size, glm::vec3 color);

    glm::vec3 position;

    std::vector<float> getGeometry(const BLOCK::SIDE side = BLOCK::SIDE::ALL, glm::uvec2 offset = glm::uvec2(0, 0));
    std::vector<uint32_t> getIndicies(const BLOCK::SIDE side = BLOCK::SIDE::ALL, const unsigned int offsetNum = 0);
    glm::vec2 getTexture() const { return textureNum; };

    int setTexture(glm::vec2 pos);

private:
    std::array<blockVertex, 4> getTopVertex();
    std::array<blockVertex, 4> getBottomVertex();

    std::array<blockVertex, 4> getSide1Vertex();
    std::array<blockVertex, 4> getSide2Vertex();
    std::array<blockVertex, 4> getSide3Vertex();
    std::array<blockVertex, 4> getSide4Vertex();


    void setTxCoords(blockVertex *v, glm::vec2 txNum, bool side = false);

    const glm::vec2 numOfTexInPNG = glm::vec2(16.0f, 16.0f);

    glm::uvec2 geomOffset;
    glm::vec3 size;
    glm::vec3 color;
    glm::vec2 textureNum = glm::vec2(0.0f);
};

