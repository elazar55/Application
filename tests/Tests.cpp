#include "acutest.h"
#include <iostream>
#include <memory>
#include <queue>
#include <SFML/Graphics.hpp>
// =============================================================================
//                              Class Application
// =============================================================================
class Application
{
  public:
    // ============================ Constructor ================================
    Application() = default;
    // ============================ Init tWindow ===============================
    void InitWindow(int         width  = 800,
                    int         height = 600,
                    std::string title  = "Title")
    {
        window_.create(sf::VideoMode(width, height), title);
    }
    // =========================================================================
    void AddDrawable(const std::shared_ptr<sf::Drawable> drawable)
    {
        draw_list_.push_back(drawable);
    }
    // ================================= Run ===================================
    void Run()
    {
        while (window_.isOpen())
        {
            PollEvents();
            Draw();
        }
    }
  private:
    // ============================= PollEvents ================================
    void PollEvents()
    {
        sf::Event event;

        while (window_.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window_.close();
            if (event.key.code == sf::Keyboard::Escape) window_.close();
        }
    }
    // ================================ Draw ===================================
    void Draw()
    {
        window_.clear();
        for (auto&& i : draw_list_)
        {
            window_.draw(*i);
        }
        window_.display();
    }
    // ============================ Member Fields ==============================
    std::vector<std::shared_ptr<sf::Drawable>> draw_list_;
    sf::RenderWindow                           window_;
};
// =============================================================================
//                                    Tests
// =============================================================================
void DrawTest()
{
    Application app;
    app.InitWindow();

    std::shared_ptr<sf::RectangleShape> rect(
        new sf::RectangleShape(sf::Vector2f(10, 10)));

    app.AddDrawable(rect);

    app.Run();
}
// =============================================================================
//                                  Test List
// =============================================================================
TEST_LIST = {
    {"DrawTest", DrawTest},
    { NULL,      NULL    }
};
