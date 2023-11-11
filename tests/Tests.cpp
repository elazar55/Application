#include "acutest.h"
#include <SFML/Graphics.hpp>

void KeyboardMapTest()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "KeyboardMapTest");
    sf::Event        event;
    TEST_CHECK(window.isOpen());

    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();
        }
    }
}

TEST_LIST = {
    {"KeyboardMapTest", KeyboardMapTest},
    { NULL,             NULL           }
};
