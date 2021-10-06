#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>

#define GRID_S 50
#define SCREEN_H 1000
#define SCREEN_W 1000
#define PI 3.14159265

float interpolate(float A,float B,float t){
    return A+t*(B-A);
}

typedef struct {
    float x, y;
} vector2;

/* Create pseudorandom direction vector
 */
vector2 randomGradient(int ix, int iy) {
    // No precomputed gradients mean this works for any number of grid coordinates
    const unsigned w = 8 * sizeof(unsigned);
    const unsigned s = w / 2; // rotation width
    unsigned a = ix, b = iy;
    a *= 3284157443; b ^= a << s | a >> w-s;
    b *= 1911520717; a ^= b << s | b >> w-s;
    a *= 2048419325;
    float random = a * (3.14159265 / ~(~0u >> 1)); // in [0, 2*Pi]
    vector2 v;
    v.x = sin(random); v.y = cos(random);
    return v;
}

// Computes the dot product of the distance and gradient vectors.
float dotGridGradient(int ix, int iy, float x, float y) {
    // Get gradient from integer coordinates
    vector2 gradient = randomGradient(ix, iy);

    // Compute the distance vector
    float dx = x - (float)ix;
    float dy = y - (float)iy;

    // Compute the dot-product
    return (dx*gradient.x + dy*gradient.y);
}

// Compute Perlin noise at coordinates x, y
float perlin(float x, float y) {
    // Determine grid cell coordinates
    int x0 = (int)x;
    int x1 = x0 + 1;
    int y0 = (int)y;
    int y1 = y0 + 1;

    // Determine interpolation weights
    // Could also use higher order polynomial/s-curve here
    //float sx = x - (float)x0;
    //float sy = y - (float)y0;

    // Interpolate between grid point gradients
    float n0, n1, ix0, ix1, value;

    //n0 = dotGridGradient(x0, y0, x, y);
    //n1 = dotGridGradient(x1, y0, x, y);
    //ix0 = interpolate(n0, n1, sx);

    //n0 = dotGridGradient(x0, y1, x, y);
    //n1 = dotGridGradient(x1, y1, x, y);
    //ix1 = interpolate(n0, n1, sx);

    //value = interpolate(ix0, ix1, sy);
    value = interpolate(interpolate(dotGridGradient(x0, y0, x, y),dotGridGradient(x1, y0, x, y),static_cast<float>(x-(x/GRID_S*GRID_S))/GRID_S) , interpolate(n0 = dotGridGradient(x0, y1, x, y),dotGridGradient(x1, y1, x, y),static_cast<float>(x-(x/GRID_S*GRID_S))/GRID_S) , static_cast<float>(y-(y/GRID_S*GRID_S))/GRID_S);
    return value;
}

int main()
{
    // Create the main window
    sf::RenderWindow app(sf::VideoMode(SCREEN_W, SCREEN_H), "SFML window");
    sf::RectangleShape pix(sf::Vector2f(1,1));


//draw
    app.clear();

    //draw the pixels
    for(float x=0;x<SCREEN_W;x++){
        for(float y=0;y<SCREEN_H;y++){
            pix.setPosition(x,y);
            float PixColor = perlin(x/GRID_S,y/GRID_S)*255;
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
