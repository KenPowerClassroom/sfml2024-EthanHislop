#pragma once

#include <SFML/Graphics.hpp>
using namespace sf;

class Block
{
public:
    Block();

    void loadContent();

    float checkBlockCollision(float t_ballSpeed, float t_ballX, float t_ballY);

    void setBlockPosition(float x, float y);

    Sprite getBody();

private:
    Sprite blockSprite;
    Texture blockTexture;
};