#include <SFML/graphics.hpp>
#include "DoublePendulum.h"
#define RES_X 800
#define RES_Y 600

int main()
{
    sf::RenderWindow window(sf::VideoMode(RES_X, RES_Y), "Double pendulum");

    DoublePendulum p(window, 5, 100, 50, RES_X/2, RES_Y/2, 20, 30);


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        p.draw();
        window.display();
    }

    return 0;
}