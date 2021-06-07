#include <SFML/Graphics.hpp>
#include <iostream>
int main()
{
    //variables
    int numberOfNeighbours = 0;
    int screenWidth = 1000;
    int screenHeight = 1000;
    int pixelSize = 10;
    int map[screenWidth / pixelSize][screenHeight / pixelSize];
    int mapBuffer[screenWidth / pixelSize][screenHeight / pixelSize];
    float Time = 2;
    sf::Clock clock;
    for (int i = 0;i<screenWidth/pixelSize;i++){
        for (int y = 0;y<screenHeight/pixelSize;y++){
            map[i][y] = 0;
        }
    }

    //generate noise
    for (int i = 0;i<screenWidth/pixelSize;i++){
        for (int y = 0;y<screenHeight/pixelSize;y++){
            map[i][y] = rand() % 2;
        }
    }


    //set things up
    sf::RenderWindow app(sf::VideoMode(screenWidth, screenHeight), "SFML window");
    sf::RectangleShape pix(sf::Vector2f(pixelSize,pixelSize));



  // the game loop
    while (app.isOpen())
    {
        //Get time since last frame
        sf::Time elapsed = clock.getElapsedTime();
        Time = elapsed.asSeconds();
        if(Time>0.08){
            elapsed = clock.restart();
            sf::Event event;
            while (app.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    app.close();
            }


            app.clear();
            for (int i = 0;i<screenWidth/pixelSize;i++){
                for (int y = 0;y<screenHeight/pixelSize;y++){
                    if(map[i][y]){
                        //draw shit
                        pix.setPosition(i*pixelSize,y*pixelSize);
                        app.draw(pix);
                    }
                    //check surroundings of the drawn cell
                    numberOfNeighbours = 0;
                    pix.setFillColor(sf::Color(255,255,255));
                    for (int w=-1;w<2;w++){
                        for(int z=-1;z<2;z++){
                            if(map[i+w][y+z]){
                                numberOfNeighbours ++;
                                if(map[i][y]){
                                    numberOfNeighbours --;
                                }
                            }
                        }
                    }
                    //turn alive or dead
                    if (numberOfNeighbours < 2){
                        mapBuffer[i][y] = 0;
                    }
                    else if (numberOfNeighbours > 3){
                        mapBuffer[i][y] = 0;
                    }
                    else if (numberOfNeighbours == 3){
                        mapBuffer[i][y] = 1;
                    }
                }
            }
            for (int i = 0;i<screenWidth/pixelSize;i++){
                for (int y = 0;y<screenHeight/pixelSize;y++){
                    mapBuffer[i][y] = map[i][y];
                }
            }
            app.display();
        }
    }
    return EXIT_SUCCESS;
}
