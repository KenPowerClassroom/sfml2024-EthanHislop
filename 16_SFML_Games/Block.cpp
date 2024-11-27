#include "Block.h"

Block::Block()
{
    loadContent();
}

void Block::loadContent()
{
    blockTexture.loadFromFile("images/arkanoid/block01.png");
    blockSprite.setTexture(blockTexture);
}

float Block::checkBlockCollision(float t_ballSpeed, float t_ballX, float t_ballY)
{
    bool blockCollCheck = FloatRect(t_ballX + 3, t_ballY + 3, 6, 6).intersects(blockSprite.getGlobalBounds());
    if (blockCollCheck)
    {
        blockSprite.setPosition(-100, 0);
        t_ballSpeed = -t_ballSpeed;
    }

    return t_ballSpeed;
}

void Block::setBlockPosition(float x, float y)
{
    blockSprite.setPosition(x, y);
}

Sprite Block::getBody()
{
    return blockSprite;
}