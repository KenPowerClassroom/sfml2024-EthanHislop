#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

int arkanoid()
{
    // Randomizer seed
    srand(time(0));

    // Set up game window
    RenderWindow app(VideoMode(520, 450), "Arkanoid!");
    app.setFramerateLimit(60);

    // Create the textures for the game objects
    Texture blockTexture, backgroundTexture, ballTexture, paddleTexture;
    blockTexture.loadFromFile("images/arkanoid/block01.png");
    backgroundTexture.loadFromFile("images/arkanoid/background.jpg");
    ballTexture.loadFromFile("images/arkanoid/ball.png");
    paddleTexture.loadFromFile("images/arkanoid/paddle.png");

    // Create the background, ball and paddle sprites and set their textures
    Sprite sBackground(backgroundTexture), sBall(ballTexture), sPaddle(paddleTexture);
    // Set the initial paddle position
    sPaddle.setPosition(300,440);

    // Create this ammount of blocks for the game
    Sprite block[1000];

    // Loop to set up blocks in their positions
    int blockIndex =0;
    for (int i = 1; i <= 10; i++)
    for (int j = 1; j <= 10; j++)
      {
         block[blockIndex].setTexture(blockTexture);
         block[blockIndex].setPosition(i*43,j*20);
         blockIndex++;
      }

    // Speed of ball in x and y direction
    float ballXSpeed = 6, ballYSpeed = 5;
    // Position of the ball
    float ballX = 300, ballY = 300;

    // Game loop
    while (app.isOpen())
    {
       Event e;
       // Close window function
       while (app.pollEvent(e))
       {
         if (e.type == Event::Closed)
             app.close();
       }

    // Move ball along x axis by dx
    ballX += ballXSpeed;
    // Check if ball is intersecting a block and reverse x direction
    for (int i = 0; i < blockIndex; i++)
        if ( FloatRect(ballX + 3, ballY + 3, 6, 6).intersects(block[i].getGlobalBounds()) ) 
             {block[i].setPosition(-100,0); ballXSpeed = -ballXSpeed;}

    // Move ball along y axis by dy
    ballY += ballYSpeed;
    // Check if ball is intersecting a block and reverse y direction
    for (int i = 0; i < blockIndex; i++)
        if ( FloatRect(ballX + 3, ballY + 3, 6, 6).intersects(block[i].getGlobalBounds()) ) 
             {block[i].setPosition(-100,0); ballYSpeed = -ballYSpeed;}

    // If ball leaves bounds, reverse direction to keep in
    if (ballX < 0 || ballX > 520)  ballXSpeed = -ballXSpeed;
    if (ballY < 0 || ballY > 450)  ballYSpeed = -ballYSpeed;

    // Move paddle controls
    if (Keyboard::isKeyPressed(Keyboard::Right)) sPaddle.move(6,0);
    if (Keyboard::isKeyPressed(Keyboard::Left)) sPaddle.move(-6,0);

    // If ball hits the paddle, move up in y axis by a random speed
    if ( FloatRect(ballX, ballY, 12, 12).intersects(sPaddle.getGlobalBounds()) ) ballYSpeed = -(rand()%5+2);

    // Update ball position
    sBall.setPosition(ballX ,ballY);

    // Draw objects
    app.clear();
    app.draw(sBackground);
    app.draw(sBall);
    app.draw(sPaddle);

    for (int i = 0; i < blockIndex; i++)
     app.draw(block[i]);

    app.display();
    }

  return 0;
}
