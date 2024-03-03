#include "acutest.h"
#include "Application.h"
#include <iostream>

void AddKeyTest()
{
    Application app;
    app.InitWindow();
    app.AddKeyPress(sf::Keyboard::Escape, std::bind(Application::Close, &app));
    app.Run();
}

void DrawTest()
{
    Application app;
    app.InitWindow();
    app.AddDrawable(std::make_unique<sf::RectangleShape>(sf::Vector2f(10, 10)));
    app.Run();
}

TEST_LIST = {
  // { "DrawTest",   DrawTest   },
  // {"AddKeyTest", AddKeyTest},
    {NULL, NULL}
};
