#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>

#define GRID_S 50
#define SCREEN_H 1000
#define SCREEN_W 1000
#define PI 3.14159265

float lerp(float A,float B,float t){
    return A+t*(B-A);
}

int main()
{
    // Create the main window
    sf::RenderWindow app(sf::VideoMode(SCREEN_W, SCREEN_H), "SFML window");
    sf::RectangleShape pix(sf::Vector2f(1,1));
    sf::VertexArray lines(sf::LinesStrip,2);
    lines[0].color = sf::Color(255,20,20);
    lines[1].color = sf::Color(255,20,20);

    int map[SCREEN_W][SCREEN_H] = {{0}};

    //generate an vector array
    for(int x=0;x<SCREEN_W/GRID_S+1;x++){
        for(int y=0;y<SCREEN_H/GRID_S+1;y++){
            map[x][y] = rand() % 360;// % 4 * 90 + 45;
        }
    }

//draw
    app.clear();

    //draw the pixels
    for(int x=0;x<SCREEN_W;x++){
        for(int y=0;y<SCREEN_H;y++){
            pix.setPosition(x,y);

            float VectorGUL[2] = {cos(map[x/GRID_S][y/GRID_S] * PI / 180),sin(map[x/GRID_S][y/GRID_S] * PI / 180)};
            float VectorGUR[2] = {cos(map[x/GRID_S+1][y/GRID_S] * PI / 180),sin(map[x/GRID_S+1][y/GRID_S] * PI / 180)};
            float VectorGDL[2] = {cos(map[x/GRID_S][y/GRID_S+1] * PI / 180),sin(map[x/GRID_S][y/GRID_S+1] * PI / 180)};
            float VectorGDR[2] = {cos(map[x/GRID_S+1][y/GRID_S+1] * PI / 180),sin(map[x/GRID_S+1][y/GRID_S+1] * PI / 180)};

            //std::cout << sqrt(pow(VectorGUL[0],2) + pow(VectorGUL[1],2)) << std::endl;

            float VectorPUL[2] = {(x-(x/GRID_S*GRID_S))/(GRID_S/2*sqrt(2)),(y-(y/GRID_S*GRID_S))/(GRID_S/2*sqrt(2))};
            float VectorPUR[2] = {((x-(x/GRID_S*GRID_S))-1)/(GRID_S/2*sqrt(2)),(y-(y/GRID_S*GRID_S))/(GRID_S/2*sqrt(2))};
            float VectorPDL[2] = {(x-(x/GRID_S*GRID_S))/(GRID_S/2*sqrt(2)),((y-(y/GRID_S*GRID_S))-1)/(GRID_S/2*sqrt(2))};
            float VectorPDR[2] = {((x-(x/GRID_S*GRID_S))-1)/(GRID_S/2*sqrt(2)),((y-(y/GRID_S*GRID_S))-1)/(GRID_S/2*sqrt(2))};

            VectorPUL[0] = VectorPUL[0] /2;
            VectorPUR[0] = VectorPUR[0] /2;
            VectorPDL[0] = VectorPDL[0] /2;
            VectorPDR[0] = VectorPDR[0] /2;

            VectorPUL[1] = VectorPUL[1] /2;
            VectorPUR[1] = VectorPUR[1] /2;
            VectorPDL[1] = VectorPDL[1] /2;
            VectorPDR[1] = VectorPDR[1] /2;

            //std::cout << sqrt(pow(VectorPUL[0],2) + pow(VectorPUL[1],2)) << std::endl;
            //for some reason this in in range from 0 to 2 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

            float dotProductUL = (VectorGUL[0] * VectorPUL[0] + VectorGUL[1] * VectorPUL[1]);
            float dotProductDL = (VectorGDL[0] * VectorPDL[0] + VectorGDL[1] * VectorPDL[1]);
            float dotProductUR = (VectorGUR[0] * VectorPUR[0] + VectorGUR[1] * VectorPUR[1]);
            float dotProductDR = (VectorGDR[0] * VectorPDR[0] + VectorGDR[1] * VectorPDR[1]);

            //lerp(dotProductUL,dotProductUR,static_cast<float>(x-(x/GRID_S*GRID_S))/GRID_S);


            // Determine grid cell coordinates
            int x0 = (int)x/GRID_S;
            int x1 = x0 + 1;
            int y0 = (int)y/GRID_S;
            int y1 = y0 + 1;

            // Determine interpolation weights
            // Could also use higher order polynomial/s-curve here
            float sx = x/GRID_S - (float)x0;
            float sy = y/GRID_S - (float)y0;

            // Interpolate between grid point gradients
            float n0, n1, ix0, ix1, value;

            //n0 = dotGridGradient(x0, y0, x, y);
            //n1 = dotGridGradient(x1, y0, x, y);
            ix0 = lerp(dotProductUL, dotProductDL, sx);

            //n0 = dotGridGradient(x0, y1, x, y);
            //n1 = dotGridGradient(x1, y1, x, y);
            ix1 = lerp(dotProductUR, dotProductDR, sx);

            //value = interpolate(ix0, ix1, sy);

            float PixColor = lerp(ix0, ix1, sy);
            PixColor = (PixColor-0.5f)*255;
            //std::cout << PixColor << std::endl;

            pix.setFillColor(sf::Color(PixColor,PixColor,PixColor));
            app.draw(pix);
        }
    }

    //draw the lines
    for(int x=0;x<SCREEN_W/GRID_S+1;x++){
        for(int y=0;y<SCREEN_H/GRID_S+1;y++){
            lines[0].position = sf::Vector2f(x*GRID_S,y*GRID_S);
            lines[1].position = sf::Vector2f(x*GRID_S+cos(map[x][y] * PI / 180)*GRID_S/2,y*GRID_S+sin(map[x][y] * PI / 180)*GRID_S/2);
            app.draw(lines);
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
