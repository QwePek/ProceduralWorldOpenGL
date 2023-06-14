#include "Block.h"

Block::Block()
{
    position = glm::vec3(0.0f, 0.0f, 0.0f);
    size = glm::vec3(1.0f, 1.0f, 1.0f);
    setTexture(BLOCK::TEXTURE::GRASS);
}

Block::Block(glm::vec3 pos, glm::vec3 size) : position(pos), size(size)
{
    setTexture(BLOCK::TEXTURE::GRASS);
}

int Block::setTexture(BLOCK::TEXTURE type)
{
    switch (type)
    {
    case BLOCK::TEXTURE::AIR:
        textureNum = glm::uvec2(15, 15); break;
    case BLOCK::TEXTURE::GRASS:
        textureNum = glm::uvec2(0, 0); break;
    case BLOCK::TEXTURE::DIRT:
        textureNum = glm::uvec2(2, 0); break;
    case BLOCK::TEXTURE::STONE:
        textureNum = glm::uvec2(1, 0); break;
    }

    textureType = type;
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

    setTxCoords(v, txN);

    return { v[0], v[1], v[2], v[3] };

}

std::array<blockVertex, 4> Block::getBottomVertex()
{
    glm::vec3 sNa2 = size / 2.0f;
    glm::vec2 txN = textureNum;

    //Oblsugiwanie innych tekstur dla boków
    if (textureType == BLOCK::TEXTURE::GRASS)
        txN = glm::vec2(2, 0);

    blockVertex v[4];

    v[0].position = { position.x - sNa2.x, position.y - sNa2.y , position.z - sNa2.z };
    v[1].position = { position.x - sNa2.x, position.y - sNa2.y, position.z + sNa2.z };
    v[2].position = { position.x + sNa2.x, position.y - sNa2.y, position.z - sNa2.z };
    v[3].position = { position.x + sNa2.x, position.y - sNa2.y, position.z + sNa2.z };

    setTxCoords(v, txN);

    return { v[0], v[1], v[2], v[3] };
}

std::array<blockVertex, 4> Block::getSide1Vertex()
{
    glm::vec3 sNa2 = size / 2.0f;
    glm::vec2 txN = textureNum;

    //Oblsugiwanie innych tekstur dla boków
    if (textureType == BLOCK::TEXTURE::GRASS)
        txN = glm::vec2(3, 0);

    blockVertex v[4];

    v[0].position = { position.x - sNa2.x, position.y - sNa2.y, position.z - sNa2.z };
    v[1].position = { position.x - sNa2.x, position.y + sNa2.y, position.z - sNa2.z };
    v[2].position = { position.x + sNa2.x, position.y - sNa2.y, position.z - sNa2.z };
    v[3].position = { position.x + sNa2.x, position.y + sNa2.y, position.z - sNa2.z };

    setTxCoords(v, txN, true);

    return { v[0], v[1], v[2], v[3] };
}

std::array<blockVertex, 4> Block::getSide2Vertex()
{
    glm::vec3 sNa2 = size / 2.0f;
    glm::vec2 txN = textureNum;

    //Oblsugiwanie innych tekstur dla boków
    if (textureType == BLOCK::TEXTURE::GRASS)
        txN = glm::vec2(3, 0);

    blockVertex v[4];

    v[0].position = { position.x - sNa2.x, position.y - sNa2.y, position.z + sNa2.z };
    v[1].position = { position.x - sNa2.x, position.y + sNa2.y, position.z + sNa2.z };
    v[2].position = { position.x + sNa2.x, position.y - sNa2.y, position.z + sNa2.z };
    v[3].position = { position.x + sNa2.x, position.y + sNa2.y, position.z + sNa2.z };

    setTxCoords(v, txN, true);

    return { v[0], v[1], v[2], v[3] };
}

std::array<blockVertex, 4> Block::getSide3Vertex()
{
    glm::vec3 sNa2 = size / 2.0f;
    glm::vec2 txN = textureNum;

    //Oblsugiwanie innych tekstur dla boków
    if (textureType == BLOCK::TEXTURE::GRASS)
        txN = glm::vec2(3, 0);

    blockVertex v[4];

    v[0].position = { position.x - sNa2.x, position.y - sNa2.y, position.z - sNa2.z };
    v[1].position = { position.x - sNa2.x, position.y + sNa2.y, position.z - sNa2.z };
    v[2].position = { position.x - sNa2.x, position.y - sNa2.y, position.z + sNa2.z };
    v[3].position = { position.x - sNa2.x, position.y + sNa2.y, position.z + sNa2.z };

    setTxCoords(v, txN, true);

    return { v[0], v[1], v[2], v[3] };
}

std::array<blockVertex, 4> Block::getSide4Vertex()
{
    glm::vec3 sNa2 = size / 2.0f;
    glm::vec2 txN = textureNum;

    //Oblsugiwanie innych tekstur dla boków
    if (textureType == BLOCK::TEXTURE::GRASS)
        txN = glm::vec2(3, 0);

    blockVertex v[4];

    v[0].position = { position.x + sNa2.x, position.y - sNa2.y, position.z - sNa2.z };
    v[1].position = { position.x + sNa2.x, position.y + sNa2.y, position.z - sNa2.z };
    v[2].position = { position.x + sNa2.x, position.y - sNa2.y, position.z + sNa2.z };
    v[3].position = { position.x + sNa2.x, position.y + sNa2.y, position.z + sNa2.z };

    setTxCoords(v, txN, true);
    
    return { v[0], v[1], v[2], v[3] };
}

void Block::setTxCoords(blockVertex* v, glm::vec2 txNum, bool side)
{
    if (!side)
    {
        v[0].txCoord = glm::vec2((1.0f / BLOCK::numOfTexInPNG.x) * (txNum.x + 1),
            1.0f - (txNum.y * (1.0f / BLOCK::numOfTexInPNG.y))); //prawy gorny

        v[1].txCoord = glm::vec2((1.0f / BLOCK::numOfTexInPNG.x) * (txNum.x + 1),
            1.0f - ((txNum.y + 1) * (1.0f / BLOCK::numOfTexInPNG.y))); //prawy dolny

        v[2].txCoord = glm::vec2((1.0f / BLOCK::numOfTexInPNG.x) * txNum.x,
            1.0f - (txNum.y * (1.0f / BLOCK::numOfTexInPNG.y))); // lewy gorny

        v[3].txCoord = glm::vec2((1.0f / BLOCK::numOfTexInPNG.x) * txNum.x,
            1.0f - ((txNum.y + 1) * (1.0f / BLOCK::numOfTexInPNG.y))); //lewy dolny

        return;
    }

    v[3].txCoord = glm::vec2((1.0f / BLOCK::numOfTexInPNG.x) * (txNum.x + 1),
        1.0f - (txNum.y * (1.0f / BLOCK::numOfTexInPNG.y))); //prawy gorny

    v[2].txCoord = glm::vec2((1.0f / BLOCK::numOfTexInPNG.x) * (txNum.x + 1),
        1.0f - ((txNum.y + 1) * (1.0f / BLOCK::numOfTexInPNG.y))); //prawy dolny

    v[1].txCoord = glm::vec2((1.0f / BLOCK::numOfTexInPNG.x) * txNum.x,
        1.0f - (txNum.y * (1.0f / BLOCK::numOfTexInPNG.y))); // lewy gorny

    v[0].txCoord = glm::vec2((1.0f / BLOCK::numOfTexInPNG.x) * txNum.x,
        1.0f - ((txNum.y + 1) * (1.0f / BLOCK::numOfTexInPNG.y))); //lewy dolny/
}

std::vector<float> Block::getGeometry(const BLOCK::SIDE side)
{
    if (textureType == BLOCK::TEXTURE::AIR)
        return { };

    glm::vec3 sNa2 = size / 2.0f;

    std::vector<float> arr;

    if (side == BLOCK::SIDE::TOP)
    {
        auto dat = getTopVertex();
        for (int i = 0; i < dat.size(); i++)
        {
            arr.push_back(dat[i].position.x);
            arr.push_back(dat[i].position.y);
            arr.push_back(dat[i].position.z);

            arr.push_back(dat[i].txCoord.x);
            arr.push_back(dat[i].txCoord.y);
        }
        return arr;
        //arr.insert(arr.end(), top.begin(), top.end());
    }
    else if (side == BLOCK::SIDE::BOTTOM)
    {
        auto dat = getBottomVertex();
        for (int i = 0; i < dat.size(); i++)
        {
            arr.push_back(dat[i].position.x);
            arr.push_back(dat[i].position.y);
            arr.push_back(dat[i].position.z);

            arr.push_back(dat[i].txCoord.x);
            arr.push_back(dat[i].txCoord.y);
        }
        return arr;
        //arr.insert(arr.end(), bottom.begin(), bottom.end());
    }
    else if (side == BLOCK::SIDE::SIDE1)
    {
        auto dat = getSide1Vertex();
        for (int i = 0; i < dat.size(); i++)
        {
            arr.push_back(dat[i].position.x);
            arr.push_back(dat[i].position.y);
            arr.push_back(dat[i].position.z);

            arr.push_back(dat[i].txCoord.x);
            arr.push_back(dat[i].txCoord.y);
        }
        return arr;
        //arr.insert(arr.end(), side1.begin(), side1.end());
    }
    else if (side == BLOCK::SIDE::SIDE2)
    {
        auto dat = getSide2Vertex();
        for (int i = 0; i < dat.size(); i++)
        {
            arr.push_back(dat[i].position.x);
            arr.push_back(dat[i].position.y);
            arr.push_back(dat[i].position.z);

            arr.push_back(dat[i].txCoord.x);
            arr.push_back(dat[i].txCoord.y);
        }
        return arr;
        //arr.insert(arr.end(), side2.begin(), side2.end());

    }
    else if (side == BLOCK::SIDE::SIDE3)
    {
        auto dat = getSide3Vertex();
        for (int i = 0; i < dat.size(); i++)
        {
            arr.push_back(dat[i].position.x);
            arr.push_back(dat[i].position.y);
            arr.push_back(dat[i].position.z);

            arr.push_back(dat[i].txCoord.x);
            arr.push_back(dat[i].txCoord.y);
        }
        return arr;
        //arr.insert(arr.end(), side3.begin(), side3.end());

    }
    else if (side == BLOCK::SIDE::SIDE4)
    {
        auto dat = getSide4Vertex();
        for (int i = 0; i < dat.size(); i++)
        {
            arr.push_back(dat[i].position.x);
            arr.push_back(dat[i].position.y);
            arr.push_back(dat[i].position.z);

            arr.push_back(dat[i].txCoord.x);
            arr.push_back(dat[i].txCoord.y);
        }
        return arr;
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

            a[0].push_back(top[i].txCoord.x);
            a[0].push_back(top[i].txCoord.y);
        }
        for (int i = 0; i < bottom.size(); i++)
        {
            a[1].push_back(bottom[i].position.x);
            a[1].push_back(bottom[i].position.y);
            a[1].push_back(bottom[i].position.z);

            a[1].push_back(bottom[i].txCoord.x);
            a[1].push_back(bottom[i].txCoord.y);
        }
        for (int i = 0; i < side1.size(); i++)
        {
            a[2].push_back(side1[i].position.x);
            a[2].push_back(side1[i].position.y);
            a[2].push_back(side1[i].position.z);

            a[2].push_back(side1[i].txCoord.x);
            a[2].push_back(side1[i].txCoord.y);
        }
        for (int i = 0; i < side2.size(); i++)
        {
            a[3].push_back(side2[i].position.x);
            a[3].push_back(side2[i].position.y);
            a[3].push_back(side2[i].position.z);

            a[3].push_back(side2[i].txCoord.x);
            a[3].push_back(side2[i].txCoord.y);
        }
        for (int i = 0; i < side3.size(); i++)
        {
            a[4].push_back(side3[i].position.x);
            a[4].push_back(side3[i].position.y);
            a[4].push_back(side3[i].position.z);

            a[4].push_back(side3[i].txCoord.x);
            a[4].push_back(side3[i].txCoord.y);
        }
        for (int i = 0; i < side4.size(); i++)
        {
            a[5].push_back(side4[i].position.x);
            a[5].push_back(side4[i].position.y);
            a[5].push_back(side4[i].position.z);

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

std::vector<uint32_t> Block::getIndicies(BLOCK::SIDE side, unsigned int offsetNum)
{
    if (textureType == BLOCK::TEXTURE::AIR)
        return { };

    if (side != BLOCK::SIDE::ALL)
    {
        std::vector<uint32_t> ind(6);
        ind[0] = 0 + offsetNum;
        ind[1] = 1 + offsetNum;
        ind[2] = 2 + offsetNum;

        ind[3] = 2 + offsetNum;
        ind[4] = 1 + offsetNum;
        ind[5] = 3 + offsetNum;

        return ind;
    }

    std::vector<uint32_t> ind(36);

    for (int i = 0; i < 6; i++)
    {
        ind[i * 6 + 0] = i * 4 + 0 + offsetNum;
        ind[i * 6 + 1] = i * 4 + 1 + offsetNum;
        ind[i * 6 + 2] = i * 4 + 2 + offsetNum;
        
        ind[i * 6 + 3] = i * 4 + 2 + offsetNum;
        ind[i * 6 + 4] = i * 4 + 1 + offsetNum;
        ind[i * 6 + 5] = i * 4 + 3 + offsetNum;
    }

    return ind;
}