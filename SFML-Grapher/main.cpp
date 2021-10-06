#include <SFML/Graphics.hpp>
#include <math.h>

#define SCREEN_W 500
#define SCREEN_H 500

int lerp(int a0,int a1,float w){
    //return (a1 - a0) * w + a0;
    //return (a1 - a0) * (3.0 - w * 2.0) * w * w + a0;
    return (a1 - a0) * ((w * (w * 6.0 - 15.0) + 10.0) * w * w * w) + a0;
}

int main()
{
    // Create the main window
    sf::RenderWindow app(sf::VideoMode(SCREEN_W, SCREEN_H), "SFML window");
    sf::RectangleShape pix(sf::Vector2f(1,1));
    sf::RectangleShape cursor(sf::Vector2f(5,5));
    pix.setFillColor(sf::Color(50,250,30));


    int pos = 100;

    while (app.isOpen())
    {
        sf::Event event;
        while (app.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                app.close();
        }

        //input
        sf::Vector2i mousePos = sf::Mouse::getPosition(app);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            pos --;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            pos ++;
        }

        app.clear();

        for(int x=0;x<SCREEN_W;x++){
            int y = lerp(pos,mousePos.y,static_cast<float>(x)/SCREEN_W);
            pix.setPosition(x,y);
            app.draw(pix);
        }
        cursor.setPosition(0,pos);
        app.draw(cursor);

        app.display();
    }

    return EXIT_SUCCESS;
}
