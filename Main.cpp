#include <SFML/graphics.hpp>
#include "DoublePendulum.h"
#include "Slider.h"
#include <time.h>

#define RES_X 800
#define RES_Y 600

int main()
{
    srand(time(NULL));
    sf::ContextSettings settings;
    settings.antialiasingLevel = 16;
    sf::RenderWindow window(sf::VideoMode(RES_X, RES_Y), "Double pendulum",sf::Style::Default, settings);
    window.setFramerateLimit(60);
    DoublePendulum p(window, 10, 10, 3, 100, 100, RES_X/2, RES_Y/2, rand()% 360, rand()%360, 10);
    Slider s_g(window, 15, 5, 10, 250, 30, 1, 1, 10, &p, &DoublePendulum::setG);
    Slider s_m1(window, 15, 40, 10, 250, 30, 1, 1, 10, &p, &DoublePendulum::setM1);
    Slider s_m2(window, 15, 75, 10, 250, 30, 1, 1, 10, &p, &DoublePendulum::setM2);
    Slider s_trail_size(window, 15, 110, 20, 250, 30, 1, 1, 255, &p, &DoublePendulum::setTrailSize);
    clock_t start= 0 , end = 0; 

    while (window.isOpen())
    {
        
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseMoved && sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                int mouseX = event.mouseMove.x;
                int mouseY = event.mouseMove.y;
                s_g.onMouseMoved(mouseX, mouseY);
                s_m1.onMouseMoved(mouseX, mouseY);
                s_m2.onMouseMoved(mouseX, mouseY);
                s_trail_size.onMouseMoved(mouseX, mouseY);
            }
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                int mouseX = event.mouseButton.x;
                int mouseY = event.mouseButton.y;
                s_g.onMouseMoved(mouseX, mouseY);
                s_m1.onMouseMoved(mouseX, mouseY);
                s_m2.onMouseMoved(mouseX, mouseY);
                s_trail_size.onMouseMoved(mouseX, mouseY);
            }
        }
        p.step(0.15);
        window.clear();
        p.draw();
        s_g.draw();
        s_m1.draw();
        s_m2.draw();
        s_trail_size.draw();
        window.display();
    }

    return 0;
}