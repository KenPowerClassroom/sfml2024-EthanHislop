#include "pch.h"
#define SFML_STATIC

#pragma comment(lib,"sfml-graphics-s-d.lib")
#pragma comment(lib,"sfml-audio-s-d.lib")
#pragma comment(lib,"sfml-system-s-d.lib")
#pragma comment(lib,"sfml-window-s-d.lib")
#pragma comment(lib,"sfml-network-s-d.lib")

#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"freetype.lib")

#include "../16_SFML_Games/Block.h"

// Test to see if setBlockPosition sets the x and y pos correctly
TEST(Block, SetBlockPos) {

	Block block;

	block.setBlockPosition(10, 10);

	EXPECT_EQ(block.getBody().getPosition().x, 10);
	EXPECT_EQ(block.getBody().getPosition().y, 10);
}

// Test to see if getting the body-position gives the right set position
TEST(Block, GetSpritePos) {

	Block block2;

	block2.setBlockPosition(10, 10);

	Vector2f vector = block2.getBody().getPosition();

	EXPECT_EQ(vector, Vector2f(10, 10)); 
}

// Test to get the block object width
TEST(Block, GetSpriteWidth) {

	Block block3;

	int width = block3.getBody().getGlobalBounds().width;
	
	EXPECT_EQ(width, 0);
}

// Test to see if a block is colliding with a ball
TEST(Block, CheckBlockCollision) {

	Block block4;

	block4.setBlockPosition(10, 10);

	EXPECT_EQ(block4.checkBlockCollision(5, 10, 10), 5);
}