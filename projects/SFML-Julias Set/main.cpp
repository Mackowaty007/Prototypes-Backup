#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    //variables
    int screenWidth = 1000;
    int screenHeight = 1000;
    int map[screenWidth][screenHeight];
    sf::RenderWindow app(sf::VideoMode(screenWidth, screenHeight), "SFML window");
    sf::RectangleShape pixel(sf::Vector2f(1,1));
    sf::Clock clock;

//  rendering
    app.clear();
    for(int x=0;x<screenWidth;x++){
        for(int y=0;y<screenHeight;y++){
            pixel.setPosition(x,y);
            app.draw(pixel);
        }
    }
    app.display();
    while (app.isOpen())
    {
        sf::Event event;
        while (app.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                app.close();
        }
    }

    return EXIT_SUCCESS;
}
