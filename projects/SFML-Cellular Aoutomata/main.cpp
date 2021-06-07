#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    //setting shit up
    int pixSize = 10;
    int screenWidth = 1000;
    int screenHeight = 1000;
    int map[screenWidth/pixSize][screenHeight/pixSize];
    sf::RenderWindow app(sf::VideoMode(screenWidth, screenHeight), "SFML window");
    sf::RectangleShape pix (sf::Vector2f(pixSize,pixSize));

    for (int x=1;x<(screenWidth-pixSize)/pixSize;x += 1){
        for (int y=1;y<(screenHeight-pixSize*14)/pixSize;y += 1){
            map[x][y] = 0;
        }
    }

    while (app.isOpen())
    {
        //closing the window
        sf::Event event;
        while (app.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                app.close();
        }

        //drawing cells
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        sf::Vector2i mousePos = sf::Mouse::getPosition(app);
            map[mousePos.x/pixSize][mousePos.y/pixSize] = 1;
        }
        else if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){
            sf::Vector2i mousePos = sf::Mouse::getPosition(app);
            map[mousePos.x/pixSize][mousePos.y/pixSize] = 0;
        }

        //rendering
        app.clear();
        for (int x=1;x<(screenWidth-pixSize)/pixSize;x += 1){
            for (int y=1;y<(screenHeight-pixSize*14)/pixSize;y += 1){
                if (map[x][y]){
                    pix.setPosition(x*pixSize,y*pixSize);
                    app.draw(pix);
                }
            }
        }
        app.display();
    }

    return EXIT_SUCCESS;
}
