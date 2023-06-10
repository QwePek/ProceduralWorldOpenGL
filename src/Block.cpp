#include "Block.h"

Block::Block()
{
    position = glm::vec3(0.0f, 0.0f, 0.0f);
    size = glm::vec3(1.0f, 1.0f, 1.0f);
    color = glm::vec3(1.0f, 1.0f, 1.0f);
    setTexture({ 0,0 });
}

Block::Block(glm::vec3 pos, glm::vec3 size) : position(pos), size(size)
{
    color = glm::vec3(1.0f, 1.0f, 1.0f);
    setTexture({ 0,0 });
}

Block::Block(glm::vec3 pos, glm::vec3 size, glm::vec3 color) : position(pos), size(size), color(color)
{
    setTexture({ 0,0 });
}

int Block::setTexture(glm::vec2 tx)
{
    if (tx.x < 0 || tx.y < 0)
        return 0;

    textureNum = tx;
    return 1;
}

std::array<blockVertex, 4> Block::getTopVertex()
{
    glm::vec3 sNa2 = size / 2.0f;
    glm::vec2 txN = textureNum;

    blockVertex v[4];

    v[0].position = { position.x - sNa2.x, position.y + sNa2.y, position.z - sNa2.z };
    v[1].position = { position.x - sNa2.x, position.y + sNa2.y, position.z + sNa2.z };
    v[2].position = { position.x + sNa2.x, position.y + sNa2.y, position.z - sNa2.z };
    v[3].position = { position.x + sNa2.x, position.y + sNa2.y, position.z + sNa2.z };

    for (int i = 0; i < 4; i++)
        v[i].color = color;

    setTxCoords(v, txN);

    return { v[0], v[1], v[2], v[3] };

}

std::array<blockVertex, 4> Block::getBottomVertex()
{
    glm::vec3 sNa2 = size / 2.0f;
    glm::vec2 txN = textureNum;

    //Oblsugiwanie innych tekstur dla boków
    if (textureNum.x == 0 && textureNum.y == 0)
        txN = glm::vec2(2, 0);

    blockVertex v[4];

    v[0].position = { position.x - sNa2.x, position.y - sNa2.y , position.z - sNa2.z };
    v[1].position = { position.x - sNa2.x, position.y - sNa2.y, position.z + sNa2.z };
    v[2].position = { position.x + sNa2.x, position.y - sNa2.y, position.z - sNa2.z };
    v[3].position = { position.x + sNa2.x, position.y - sNa2.y, position.z + sNa2.z };

    for (int i = 0; i < 4; i++)
        v[i].color = color;

    setTxCoords(v, txN);

    return { v[0], v[1], v[2], v[3] };
}

std::array<blockVertex, 4> Block::getSide1Vertex()
{
    glm::vec3 sNa2 = size / 2.0f;
    glm::vec2 txN = textureNum;

    //Oblsugiwanie innych tekstur dla boków
    if (textureNum.x == 0 && textureNum.y == 0)
        txN = glm::vec2(3, 0);

    blockVertex v[4];

    v[0].position = { position.x - sNa2.x, position.y - sNa2.y, position.z - sNa2.z };
    v[1].position = { position.x - sNa2.x, position.y + sNa2.y, position.z - sNa2.z };
    v[2].position = { position.x + sNa2.x, position.y - sNa2.y, position.z - sNa2.z };
    v[3].position = { position.x + sNa2.x, position.y + sNa2.y, position.z - sNa2.z };

    for (int i = 0; i < 4; i++)
        v[i].color = color;

    setTxCoords(v, txN, true);

    return { v[0], v[1], v[2], v[3] };
}

std::array<blockVertex, 4> Block::getSide2Vertex()
{
    glm::vec3 sNa2 = size / 2.0f;
    glm::vec2 txN = textureNum;

    //Oblsugiwanie innych tekstur dla boków
    if (textureNum.x == 0 && textureNum.y == 0)
        txN = glm::vec2(3, 0);

    blockVertex v[4];

    v[0].position = { position.x - sNa2.x, position.y - sNa2.y, position.z + sNa2.z };
    v[1].position = { position.x - sNa2.x, position.y + sNa2.y, position.z + sNa2.z };
    v[2].position = { position.x + sNa2.x, position.y - sNa2.y, position.z + sNa2.z };
    v[3].position = { position.x + sNa2.x, position.y + sNa2.y, position.z + sNa2.z };

    for (int i = 0; i < 4; i++)
        v[i].color = color;

    setTxCoords(v, txN, true);

    return { v[0], v[1], v[2], v[3] };
}

std::array<blockVertex, 4> Block::getSide3Vertex()
{
    glm::vec3 sNa2 = size / 2.0f;
    glm::vec2 txN = textureNum;

    //Oblsugiwanie innych tekstur dla boków
    if (textureNum.x == 0 && textureNum.y == 0)
        txN = glm::vec2(3, 0);

    blockVertex v[4];

    v[0].position = { position.x - sNa2.x, position.y - sNa2.y, position.z - sNa2.z };
    v[1].position = { position.x - sNa2.x, position.y + sNa2.y, position.z - sNa2.z };
    v[2].position = { position.x - sNa2.x, position.y - sNa2.y, position.z + sNa2.z };
    v[3].position = { position.x - sNa2.x, position.y + sNa2.y, position.z + sNa2.z };

    for (int i = 0; i < 4; i++)
        v[i].color = color;

    setTxCoords(v, txN, true);

    return { v[0], v[1], v[2], v[3] };
}

std::array<blockVertex, 4> Block::getSide4Vertex()
{
    glm::vec3 sNa2 = size / 2.0f;
    glm::vec2 txN = textureNum;

    //Oblsugiwanie innych tekstur dla boków
    if (textureNum.x == 0 && textureNum.y == 0)
        txN = glm::vec2(3, 0);

    blockVertex v[4];

    v[0].position = { position.x + sNa2.x, position.y - sNa2.y, position.z - sNa2.z };
    v[1].position = { position.x + sNa2.x, position.y + sNa2.y, position.z - sNa2.z };
    v[2].position = { position.x + sNa2.x, position.y - sNa2.y, position.z + sNa2.z };
    v[3].position = { position.x + sNa2.x, position.y + sNa2.y, position.z + sNa2.z };

    for (int i = 0; i < 4; i++)
        v[i].color = color;

    setTxCoords(v, txN, true);
    
    return { v[0], v[1], v[2], v[3] };
}

void Block::setTxCoords(blockVertex* v, glm::vec2 txNum, bool side)
{
    if (!side)
    {
        v[0].txCoord = glm::vec2((1.0f / numOfTexInPNG.x) * (txNum.x + 1),
            1.0f - (txNum.y * (1.0f / numOfTexInPNG.y))); //prawy gorny

        v[1].txCoord = glm::vec2((1.0f / numOfTexInPNG.x) * (txNum.x + 1),
            1.0f - ((txNum.y + 1) * (1.0f / numOfTexInPNG.y))); //prawy dolny

        v[2].txCoord = glm::vec2((1.0f / numOfTexInPNG.x) * txNum.x,
            1.0f - (txNum.y * (1.0f / numOfTexInPNG.y))); // lewy gorny

        v[3].txCoord = glm::vec2((1.0f / numOfTexInPNG.x) * txNum.x,
            1.0f - ((txNum.y + 1) * (1.0f / numOfTexInPNG.y))); //lewy dolny

        return;
    }

    v[3].txCoord = glm::vec2((1.0f / numOfTexInPNG.x) * (txNum.x + 1),
        1.0f - (txNum.y * (1.0f / numOfTexInPNG.y))); //prawy gorny

    v[2].txCoord = glm::vec2((1.0f / numOfTexInPNG.x) * (txNum.x + 1),
        1.0f - ((txNum.y + 1) * (1.0f / numOfTexInPNG.y))); //prawy dolny

    v[1].txCoord = glm::vec2((1.0f / numOfTexInPNG.x) * txNum.x,
        1.0f - (txNum.y * (1.0f / numOfTexInPNG.y))); // lewy gorny

    v[0].txCoord = glm::vec2((1.0f / numOfTexInPNG.x) * txNum.x,
        1.0f - ((txNum.y + 1) * (1.0f / numOfTexInPNG.y))); //lewy dolny/
}

std::vector<float> Block::getGeometry(const BLOCK::SIDE side)
{
    if (textureNum.x == 2 && textureNum.y == 0)//AIR JAK NA RAZIE POPRAW TO POTEM
        return { };

    glm::vec3 sNa2 = size / 2.0f;

    std::vector<float> arr;

    if (side == BLOCK::SIDE::TOP)
    {
        auto top = getTopVertex();
        //arr.insert(arr.end(), top.begin(), top.end());
    }
    else if (side == BLOCK::SIDE::BOTTOM)
    {
        auto bottom = getBottomVertex();
        //arr.insert(arr.end(), bottom.begin(), bottom.end());
    }
    else if (side == BLOCK::SIDE::SIDE1)
    {
        auto side1 = getSide1Vertex();
        //arr.insert(arr.end(), side1.begin(), side1.end());
    }
    else if (side == BLOCK::SIDE::SIDE2)
    {
        auto side2 = getSide2Vertex();
        //arr.insert(arr.end(), side2.begin(), side2.end());

    }
    else if (side == BLOCK::SIDE::SIDE3)
    {
        auto side3 = getSide3Vertex();
        //arr.insert(arr.end(), side3.begin(), side3.end());

    }
    else if (side == BLOCK::SIDE::SIDE4)
    {
        auto side4 = getSide4Vertex();
        //arr.insert(arr.end(), side4.begin(), side4.end());
    }
    else
    {
        auto top = getTopVertex();
        auto bottom = getBottomVertex();
        auto side1 = getSide1Vertex();
        auto side2 = getSide2Vertex();
        auto side3 = getSide3Vertex();
        auto side4 = getSide4Vertex();

        //DWBUGI KRUAD
        std::vector<float> a[6];
        for (int i = 0; i < top.size(); i++)
        {
            a[0].push_back(top[i].position.x);
            a[0].push_back(top[i].position.y);
            a[0].push_back(top[i].position.z);

            a[0].push_back(top[i].color.x);
            a[0].push_back(top[i].color.y);
            a[0].push_back(top[i].color.z);

            a[0].push_back(top[i].txCoord.x);
            a[0].push_back(top[i].txCoord.y);
        }
        for (int i = 0; i < top.size(); i++)
        {
            a[1].push_back(bottom[i].position.x);
            a[1].push_back(bottom[i].position.y);
            a[1].push_back(bottom[i].position.z);

            a[1].push_back(bottom[i].color.x);
            a[1].push_back(bottom[i].color.y);
            a[1].push_back(bottom[i].color.z);

            a[1].push_back(bottom[i].txCoord.x);
            a[1].push_back(bottom[i].txCoord.y);
        }
        for (int i = 0; i < top.size(); i++)
        {
            a[2].push_back(side1[i].position.x);
            a[2].push_back(side1[i].position.y);
            a[2].push_back(side1[i].position.z);

            a[2].push_back(side1[i].color.x);
            a[2].push_back(side1[i].color.y);
            a[2].push_back(side1[i].color.z);

            a[2].push_back(side1[i].txCoord.x);
            a[2].push_back(side1[i].txCoord.y);
        }
        for (int i = 0; i < top.size(); i++)
        {
            a[3].push_back(side2[i].position.x);
            a[3].push_back(side2[i].position.y);
            a[3].push_back(side2[i].position.z);

            a[3].push_back(side2[i].color.x);
            a[3].push_back(side2[i].color.y);
            a[3].push_back(side2[i].color.z);

            a[3].push_back(side2[i].txCoord.x);
            a[3].push_back(side2[i].txCoord.y);
        }
        for (int i = 0; i < top.size(); i++)
        {
            a[4].push_back(side3[i].position.x);
            a[4].push_back(side3[i].position.y);
            a[4].push_back(side3[i].position.z);

            a[4].push_back(side3[i].color.x);
            a[4].push_back(side3[i].color.y);
            a[4].push_back(side3[i].color.z);

            a[4].push_back(side3[i].txCoord.x);
            a[4].push_back(side3[i].txCoord.y);
        }
        for (int i = 0; i < top.size(); i++)
        {
            a[5].push_back(side4[i].position.x);
            a[5].push_back(side4[i].position.y);
            a[5].push_back(side4[i].position.z);

            a[5].push_back(side4[i].color.x);
            a[5].push_back(side4[i].color.y);
            a[5].push_back(side4[i].color.z);

            a[5].push_back(side4[i].txCoord.x);
            a[5].push_back(side4[i].txCoord.y);
        }


        for(int j=0;j<6;j++)
            arr.insert(arr.end(), a[j].begin(), a[j].end());

        //arr.insert(arr.end(), top.data(), top.data() + top.size() * sizeof(blockVertex));
        //arr.insert(arr.end(), bottom.begin(), bottom.end());
        //arr.insert(arr.end(), side1.begin(), side1.end());
        //arr.insert(arr.end(), side2.begin(), side2.end());
        //arr.insert(arr.end(), side3.begin(), side3.end());
        //arr.insert(arr.end(), side4.begin(), side4.end());
    }

    return arr;
}

std::vector<uint32_t> Block::getIndicies(const BLOCK::SIDE side, const unsigned int offsetNum)
{
    if (textureNum.x == 2 && textureNum.y == 0)//AIR JAK NA RAZIE POPRAW TO POTEM
        return { };

    std::vector<uint32_t> ind(36);

    for (int i = 0; i < 36; i += 6)
    {
        ind[i] = i + offsetNum;
        ind[i + 1] = i + 1 + offsetNum;
        ind[i + 2] = i + 2 + offsetNum;

        ind[i + 3] = i + 2 + offsetNum;
        ind[i + 4] = i + 1 + offsetNum;
        ind[i + 5] = i + 3 + offsetNum;
    }

    return ind;
}
