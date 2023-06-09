#include "Block.h"
#include <iostream>
#include <array>

std::array<blockVertex, 24> Block::createBlock()
{
    glm::vec3 sNa2 = size / 2.0f;

    blockVertex v[24];

    v[0].position = { position.x - sNa2.x, position.y - sNa2.y, position.z - sNa2.z };
    v[1].position = { position.x - sNa2.x, position.y + sNa2.y, position.z - sNa2.z };
    v[2].position = { position.x + sNa2.x, position.y - sNa2.y, position.z - sNa2.z };
    v[3].position = { position.x + sNa2.x, position.y + sNa2.y, position.z - sNa2.z };
    
    v[4].position = { position.x - sNa2.x, position.y - sNa2.y, position.z + sNa2.z };
    v[5].position = { position.x - sNa2.x, position.y + sNa2.y, position.z + sNa2.z };
    v[6].position = { position.x + sNa2.x, position.y - sNa2.y, position.z + sNa2.z };
    v[7].position = { position.x + sNa2.x, position.y + sNa2.y, position.z + sNa2.z };
    
    v[8].position = { position.x - sNa2.x, position.y - sNa2.y, position.z - sNa2.z };
    v[9].position = { position.x - sNa2.x, position.y + sNa2.y, position.z - sNa2.z };
    v[10].position = { position.x - sNa2.x, position.y - sNa2.y, position.z + sNa2.z };
    v[11].position = { position.x - sNa2.x, position.y + sNa2.y, position.z + sNa2.z };
    
    v[12].position = { position.x + sNa2.x, position.y - sNa2.y, position.z - sNa2.z };
    v[13].position = { position.x + sNa2.x, position.y + sNa2.y, position.z - sNa2.z };
    v[14].position = { position.x + sNa2.x, position.y - sNa2.y, position.z + sNa2.z };
    v[15].position = { position.x + sNa2.x, position.y + sNa2.y, position.z + sNa2.z };
    
    v[16].position = { position.x - sNa2.x, position.y - sNa2.y , position.z - sNa2.z };
    v[17].position = { position.x - sNa2.x, position.y - sNa2.y, position.z + sNa2.z };
    v[18].position = { position.x + sNa2.x, position.y - sNa2.y, position.z - sNa2.z };
    v[19].position = { position.x + sNa2.x, position.y - sNa2.y, position.z + sNa2.z };
    
    v[20].position = { position.x - sNa2.x, position.y + sNa2.y, position.z - sNa2.z };
    v[21].position = { position.x - sNa2.x, position.y + sNa2.y, position.z + sNa2.z };
    v[22].position = { position.x + sNa2.x, position.y + sNa2.y, position.z - sNa2.z };
    v[23].position = { position.x + sNa2.x, position.y + sNa2.y, position.z + sNa2.z };
    

    int numOfTexInX = 16;
    int numOfTexInY = 16;

    for (int i = 0; i < 24; i++)
    {
        v[i].color = color;

        if (i % 4 == 3)
        {
            v[i].txCoord = glm::vec2((1.0f / numOfTexInX) * textureNum.x,
                1.0f - ((textureNum.y + 1) * (1.0f / numOfTexInY))); //lewy dolny
        }
        else if (i % 4 == 2)
        {
                                                    //To jest ile t jest
            v[i].txCoord = glm::vec2((1.0f / numOfTexInX) * textureNum.x, 
                1.0f - (textureNum.y * (1.0f / numOfTexInY))); // lewy gorny
        }
        else if (i % 4 == 1)
        {
            v[i].txCoord = glm::vec2((1.0f / numOfTexInX) * (textureNum.x + 1),
                1.0f - ((textureNum.y + 1) * (1.0f / numOfTexInY))); //prawy dolny
        }
        else if (i % 4 == 0)
        {
            v[i].txCoord = glm::vec2((1.0f / numOfTexInX) * (textureNum.x + 1),
                1.0f - (textureNum.y * (1.0f / numOfTexInY))); //prawy gorny
        }
    }

    return { v[0], v[1], v[2], v[3],v[4], v[5], v[6], v[7],v[8], v[9], v[10], v[11],
            v[12], v[13], v[14], v[15],v[16], v[17], v[18], v[19],v[20], v[21], v[22], v[23] };
}
