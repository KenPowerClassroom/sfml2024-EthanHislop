#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

// Const variables
const int SCREEN_WIDTH = 520;
const int SCREEN_HEIGHT = 450;
const int BLOCK_NUM = 1000;

class Block
{
public:
    Block()
    {
        loadContent();
    }

    void loadContent()
    {
        blockTexture.loadFromFile("images/arkanoid/block01.png");
        blockSprite.setTexture(blockTexture);
    }

    float checkBlockCollision(float t_ballSpeed, float t_ballX, float t_ballY)
    {
        bool blockCollCheck = FloatRect(t_ballX + 3, t_ballY + 3, 6, 6).intersects(blockSprite.getGlobalBounds());
        if (blockCollCheck)
        {
            blockSprite.setPosition(-100, 0); t_ballSpeed = -t_ballSpeed;
        }

        return t_ballSpeed;
    }

    void setBlockPosition(float x, float y)
    {
        blockSprite.setPosition(x, y);
    }

    Sprite getBody()
    {
        return blockSprite;
    }

private:
    Sprite blockSprite;
    Texture blockTexture;
};

int arkanoid()
{
    // Randomizer seed
    srand(time(0));

    // Set up game window
    RenderWindow app(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Arkanoid!");
    app.setFramerateLimit(60);

    // Create the textures for the game objects
    Texture backgroundTexture, ballTexture, paddleTexture;
    backgroundTexture.loadFromFile("images/arkanoid/background.jpg");
    ballTexture.loadFromFile("images/arkanoid/ball.png");
    paddleTexture.loadFromFile("images/arkanoid/paddle.png");

    // Create the background, ball and paddle sprites and set their textures
    Sprite sBackground(backgroundTexture), sBall(ballTexture), sPaddle(paddleTexture);
    // Set the initial paddle position
    sPaddle.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 10);

    Block block[BLOCK_NUM];

    // Loop to set up blocks in their positions
    int currentBlockIndex = 0;
    for (int row = 1; row <= 10; row++)
    for (int column = 1; column <= 10; column++)
    {
        block[currentBlockIndex].setBlockPosition(row * block[currentBlockIndex].getBody().getGlobalBounds().width, column * block[currentBlockIndex].getBody().getGlobalBounds().height);
        currentBlockIndex++;
    }

    // Speed of ball in x and y direction
    float ballXSpeed = 6, ballYSpeed = 5;
    // Position of the ball
    float ballX = 300, ballY = 300;

    // Game loop
    while (app.isOpen())
    {
        Event event;
        // Close window function
        while (app.pollEvent(event))
        {
            if (event.type == Event::Closed)
            app.close();
        }

        // Move ball along x axis by dx
        ballX += ballXSpeed;
        // Check if ball is intersecting a block and reverse x direction
        ballXSpeed = block->checkBlockCollision(ballXSpeed, ballX, ballY);

        // Move ball along y axis by dy
        ballY += ballYSpeed;
        // Check if ball is intersecting a block and reverse y direction
        ballYSpeed = block->checkBlockCollision(ballYSpeed, ballX, ballY);

        // If ball leaves bounds, reverse direction to keep in
        if (ballX < 0 || ballX > SCREEN_WIDTH)  ballXSpeed = -ballXSpeed;
        if (ballY < 0 || ballY > SCREEN_HEIGHT)  ballYSpeed = -ballYSpeed;

        // Move paddle controls
        if (Keyboard::isKeyPressed(Keyboard::Right)) sPaddle.move(6, 0);
        if (Keyboard::isKeyPressed(Keyboard::Left)) sPaddle.move(-6, 0);

        // If ball hits the paddle, move up in y axis by a random speed
        bool paddleCollCheck = FloatRect(ballX, ballY, 12, 12).intersects(sPaddle.getGlobalBounds());
        if (paddleCollCheck)
        {
            ballYSpeed = -(rand() % 5 + 2);
        }

        // Update ball position
        sBall.setPosition(ballX, ballY);

        // Draw objects
        app.clear();
        app.draw(sBackground);
        app.draw(sBall);
        app.draw(sPaddle);
        for (int i = 0; i < BLOCK_NUM; i++)
        {
            app.draw(block[i].getBody());
        }

        app.display();
    }

  return 0;
}
