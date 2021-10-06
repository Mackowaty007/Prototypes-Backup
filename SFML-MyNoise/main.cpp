#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>

#define GRID_S 50
#define SCREEN_H 1000
#define SCREEN_W 1000
#define PI 3.14159265

float lerp(float A,float B,float t){
    //return A+t*(B-A);
    return (B - A) * (3.0 - t * 2.0) * t * t + A;
}

int main()
{
    // Create the main window
    sf::RenderWindow app(sf::VideoMode(SCREEN_W, SCREEN_H), "SFML window");
    sf::RectangleShape pix(sf::Vector2f(1,1));

    float map[SCREEN_W][SCREEN_H] = {{0}};
    float randomGrid[SCREEN_W/GRID_S][SCREEN_H/GRID_S] = {{0}};

    //generate random grid
    for(int x=0;x<SCREEN_W/GRID_S;x++){
        for(int y=0;y<SCREEN_H/GRID_S;y++){
            randomGrid[x][y] = rand() % 255;
        }
    }

    //interpolate between grid space
    for(int x=0;x<SCREEN_W;x++){
        for(int y=0;y<SCREEN_H;y++){
            map[x][y] = lerp(randomGrid[x/GRID_S][y/GRID_S],randomGrid[x/GRID_S+1][y/GRID_S],static_cast<float>(x-(x/GRID_S*GRID_S))/GRID_S);
            //std::cout << static_cast<float>(x-(x/GRID_S*GRID_S))/GRID_S << std::endl;
        }
    }


//draw
    app.clear();

    //draw the pixels from map array
    for(int x=0;x<SCREEN_W;x++){
        for(int y=0;y<SCREEN_H;y++){
            pix.setPosition(x,y);
            float PixColor = map[x][y];
            pix.setFillColor(sf::Color(PixColor,PixColor,PixColor));
            app.draw(pix);
        }
    }

    app.display();

	// Start the game loop
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
