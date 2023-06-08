#include "Block.h"
#include <iostream>
#include <array>

std::array<blockVertex, 24> Block::createBlock()
{
    glm::vec3 sNa2 = size / 2.0f;

    blockVertex v0;
    v0.position = { position.x - sNa2.x, position.y - sNa2.y, position.z - sNa2.z };
    v0.color = color;
    v0.txCoord = glm::vec2(0.0f, 0.0f);

    blockVertex v1;
    v1.position = { position.x - sNa2.x, position.y + sNa2.y, position.z - sNa2.z };
    v1.color = color;
    v1.txCoord = glm::vec2(0.0f, 1.0f);

    blockVertex v2;
    v2.position = { position.x + sNa2.x, position.y - sNa2.y, position.z - sNa2.z };
    v2.color = color;
    v2.txCoord = glm::vec2(1.0f, 0.0f);

    blockVertex v3;
    v3.position = { position.x + sNa2.x, position.y + sNa2.y, position.z - sNa2.z };
    v3.color = color;
    v3.txCoord = glm::vec2(1.0f, 1.0f);



    //
    blockVertex v4;
    v4.position = { position.x - sNa2.x, position.y - sNa2.y, position.z + sNa2.z };
    v4.color = color;
    v4.txCoord = glm::vec2(0.0f, 0.0f);

    blockVertex v5;
    v5.position = { position.x - sNa2.x, position.y + sNa2.y, position.z + sNa2.z };
    v5.color = color;
    v5.txCoord = glm::vec2(0.0f, 1.0f);

    blockVertex v6;
    v6.position = { position.x + sNa2.x, position.y - sNa2.y, position.z + sNa2.z };
    v6.color = color;
    v6.txCoord = glm::vec2(1.0f, 0.0f);

    blockVertex v7;
    v7.position = { position.x + sNa2.x, position.y + sNa2.y, position.z + sNa2.z };
    v7.color = color;
    v7.txCoord = glm::vec2(1.0f, 1.0f);
    //

        //
    blockVertex v8;
    v8.position = { position.x - sNa2.x, position.y - sNa2.y, position.z - sNa2.z };
    v8.color = color;
    v8.txCoord = glm::vec2(0.0f, 0.0f);

    blockVertex v9;
    v9.position = { position.x - sNa2.x, position.y + sNa2.y, position.z - sNa2.z };
    v9.color = color;
    v9.txCoord = glm::vec2(0.0f, 1.0f);

    blockVertex v10;
    v10.position = { position.x - sNa2.x, position.y - sNa2.y, position.z + sNa2.z };
    v10.color = color;
    v10.txCoord = glm::vec2(1.0f, 0.0f);

    blockVertex v11;
    v11.position = { position.x - sNa2.x, position.y + sNa2.y, position.z + sNa2.z };
    v11.color = color;
    v11.txCoord = glm::vec2(1.0f, 1.0f);
    //


    blockVertex v12;
    v12.position = { position.x + sNa2.x, position.y - sNa2.y, position.z - sNa2.z };
    v12.color = color;
    v12.txCoord = glm::vec2(0.0f, 0.0f);

    blockVertex v13;
    v13.position = { position.x + sNa2.x, position.y + sNa2.y, position.z - sNa2.z };
    v13.color = color;
    v13.txCoord = glm::vec2(0.0f, 1.0f);

    blockVertex v14;
    v14.position = { position.x + sNa2.x, position.y - sNa2.y, position.z + sNa2.z };
    v14.color = color;
    v14.txCoord = glm::vec2(1.0f, 0.0f);

    blockVertex v15;
    v15.position = { position.x + sNa2.x, position.y + sNa2.y, position.z + sNa2.z };
    v15.color = color;
    v15.txCoord = glm::vec2(1.0f, 1.0f);

    ///

        //
    blockVertex v16;
    v16.position = { position.x - sNa2.x, position.y - sNa2.y , position.z - sNa2.z };
    v16.color = color;
    v16.txCoord = glm::vec2(0.0f, 0.0f);

    blockVertex v17;
    v17.position = { position.x - sNa2.x, position.y - sNa2.y, position.z + sNa2.z };
    v17.color = color;
    v17.txCoord = glm::vec2(0.0f, 1.0f);

    blockVertex v18;
    v18.position = { position.x + sNa2.x, position.y - sNa2.y, position.z - sNa2.z };
    v18.color = color;
    v18.txCoord = glm::vec2(1.0f, 0.0f);

    blockVertex v19;
    v19.position = { position.x + sNa2.x, position.y - sNa2.y, position.z + sNa2.z };
    v19.color = color;
    v19.txCoord = glm::vec2(1.0f, 1.0f);
    ///

    blockVertex v20;
    v20.position = { position.x - sNa2.x, position.y + sNa2.y, position.z - sNa2.z };
    v20.color = color;
    v20.txCoord = glm::vec2(0.0f, 0.0f);

    blockVertex v21;
    v21.position = { position.x - sNa2.x, position.y + sNa2.y, position.z + sNa2.z };
    v21.color = color;
    v21.txCoord = glm::vec2(0.0f, 1.0f);

    blockVertex v22;
    v22.position = { position.x + sNa2.x, position.y + sNa2.y, position.z - sNa2.z };
    v22.color = color;
    v22.txCoord = glm::vec2(1.0f, 0.0f);

    blockVertex v23;
    v23.position = { position.x + sNa2.x, position.y + sNa2.y, position.z + sNa2.z };
    v23.color = color;
    v23.txCoord = glm::vec2(1.0f, 1.0f);

    return { v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,
            v13,v14,v15,v16,v17,v18,v19,v20,v21,v22,v23 };
}
