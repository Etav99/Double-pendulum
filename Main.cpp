#include <SFML/graphics.hpp>
#include "DoublePendulum.h"
#include <time.h>
#define RES_X 800
#define RES_Y 600

int main()
{
    srand(time(NULL));
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(RES_X, RES_Y), "Double pendulum",sf::Style::Default, settings);
    window.setFramerateLimit(60);
    DoublePendulum p(window, 10, 10, 2, 100, 50, RES_X/2, RES_Y/2, rand()% 360, rand()%360, 10);
    clock_t start= 0 , end = 0; 

    while (window.isOpen())
    {
        
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        p.step(0.1);
        window.clear();
        p.draw();
        window.display();
    }

    return 0;
}