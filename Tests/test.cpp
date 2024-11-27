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

TEST(Block, SetBlockPos) {

	Block block;

	block.setBlockPosition(10, 10);

	EXPECT_EQ(block.getBody().getPosition().x, 10);
	EXPECT_EQ(block.getBody().getPosition().y, 10);
}