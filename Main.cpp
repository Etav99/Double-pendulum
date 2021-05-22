#include <SFML/graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "Double pendulum");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.display();
    }

    return 0;
}