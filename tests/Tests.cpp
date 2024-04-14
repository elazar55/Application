#include "acutest.h"
#include "MyWindow.h"
#include <iostream>
// =============================================================================
//                                 AddKeyTest
// =============================================================================
void AddKeyTest()
{
    MyWindow app;
    app.InitWindow();
    app.AddKeyPress(sf::Keyboard::Escape, std::bind(MyWindow::Close, &app));
    app.Run();
}
// =============================================================================
//                                  DrawTest
// =============================================================================
void DrawTest()
{
    MyWindow app;
    app.InitWindow();
    app.AddDrawable(std::make_unique<sf::RectangleShape>(sf::Vector2f(10, 10)));
    app.Run();
}
// =============================================================================
//                                  TEST_LIST
// =============================================================================
TEST_LIST = {
    {NULL, NULL}
};
