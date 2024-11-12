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
    Texture t1,t2,t3,t4;
    t1.loadFromFile("images/arkanoid/block01.png");
    t2.loadFromFile("images/arkanoid/background.jpg");
    t3.loadFromFile("images/arkanoid/ball.png");
    t4.loadFromFile("images/arkanoid/paddle.png");

    // Create the background, ball and paddle sprites and set their textures
    Sprite sBackground(t2), sBall(t3), sPaddle(t4);
    // Set the initial paddle position
    sPaddle.setPosition(300,440);

    // Create this ammount of blocks for the game
    Sprite block[1000];

    // Loop to set up blocks in their positions
    int n=0;
    for (int i=1;i<=10;i++)
    for (int j=1;j<=10;j++)
      {
         block[n].setTexture(t1);
         block[n].setPosition(i*43,j*20);
         n++;
      }

    // Speed of ball in x and y direction
    float dx=6, dy=5;
    // Position of the ball
    float x=300, y=300;

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
    x+=dx;
    // Check if ball is intersecting a block and reverse x direction
    for (int i=0;i<n;i++)
        if ( FloatRect(x+3,y+3,6,6).intersects(block[i].getGlobalBounds()) ) 
             {block[i].setPosition(-100,0); dx=-dx;}

    // Move ball along y axis by dy
    y+=dy;
    // Check if ball is intersecting a block and reverse y direction
    for (int i=0;i<n;i++)
        if ( FloatRect(x+3,y+3,6,6).intersects(block[i].getGlobalBounds()) ) 
             {block[i].setPosition(-100,0); dy=-dy;}

    // If ball leaves bounds, reverse direction to keep in
    if (x<0 || x>520)  dx=-dx;
    if (y<0 || y>450)  dy=-dy;

    // Move paddle controls
    if (Keyboard::isKeyPressed(Keyboard::Right)) sPaddle.move(6,0);
    if (Keyboard::isKeyPressed(Keyboard::Left)) sPaddle.move(-6,0);

    // If ball hits the paddle, move up in y axis by a random speed
    if ( FloatRect(x,y,12,12).intersects(sPaddle.getGlobalBounds()) ) dy=-(rand()%5+2);

    // Update ball position
    sBall.setPosition(x,y);

    // Draw objects
    app.clear();
    app.draw(sBackground);
    app.draw(sBall);
    app.draw(sPaddle);

    for (int i=0;i<n;i++)
     app.draw(block[i]);

    app.display();
    }

  return 0;
}
