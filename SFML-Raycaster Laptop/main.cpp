#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#define PI 3.14159265

int main()
{
    sf::VertexArray lines(sf::LineStrip,2);
    //setup
    int screenWidth = 1000; int screenHeight = 500; int pixSize = 50; int arraySize = 10; sf::Vector2f playerPos(300,300); int playerSize = 20; float playerDirection = 0;
    float resultCos, resultSin;
    int map[arraySize][arraySize] =
    {//10 per 10 array
        {1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,1,0,1,0,1},
        {1,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,1,0,0,0,0,1},
        {1,0,0,0,0,0,1,0,0,1},
        {1,0,0,0,0,0,1,0,0,1},
        {1,1,1,1,0,0,1,0,0,1},
        {1,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1}
    };
    sf::RenderWindow app(sf::VideoMode(screenWidth, screenHeight), "SFML window");
    sf::RectangleShape pix(sf::Vector2f(pixSize-1,pixSize-1));
    sf::RectangleShape player(sf::Vector2f(playerSize,playerSize));
    player.setPosition(100,100);
    player.setFillColor(sf::Color(100,200,10));
    pix.setFillColor(sf::Color(10,100,50));

    while (app.isOpen())
    {
        sf::Event event;
        while (app.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                app.close();
        }
        //calculate the ray position
        resultCos = cos(playerDirection * PI / 180.0f);
        resultSin = sin(playerDirection * PI / 180.0f);

        //input
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
            player.move(resultCos/10,resultSin/10);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
            player.move(-resultCos/10,-resultSin/10);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
            playerDirection -= 0.1f;
            //i think this is disposable, the circle loops nicle without this
            if (playerDirection < 0){
                playerDirection = 360;
            }

        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
            playerDirection += 0.1f;
            //i think this is disposable, the circle loops nicle without this
            if (playerDirection > 360){
                playerDirection = 0;
            }
        }

        //frame rendering
        app.clear();
        //drawing the map
        for(int x=0;x<arraySize;x++){
            for(int y=0;y<arraySize;y++){
                if(map[y][x]){
                    pix.setPosition(x*pixSize,y*pixSize);
                    app.draw(pix);
                }
            }
        }
        //drawing the player
        app.draw(player);
        std::cout << playerDirection << std::endl;
        //drawing rays
        lines[0].position = sf::Vector2f(player.getPosition());
        lines[1].position = sf::Vector2f(player.getPosition().x + resultCos * 50, player.getPosition().y + resultSin * 50);
        app.draw(lines);

        app.display();
    }
    return EXIT_SUCCESS;
}
