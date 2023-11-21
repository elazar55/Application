#include "acutest.h"
#include <functional>
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
    void AddDrawable(std::unique_ptr<sf::Drawable> drawable)
    {
        draw_list_.push_back(std::move(drawable));
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
    // =========================================================================
    void AddKey(sf::Keyboard::Key key, std::function<void()> func)
    {
        key_map_.emplace(key, func);
    }
  private:
    // ============================= PollEvents ================================
    void PollEvents()
    {
        sf::Event event;

        while (window_.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window_.close();
            if (event.type == sf::Event::KeyPressed)
            {
                if (key_map_[event.key.code] != nullptr)
                {
                    key_map_[event.key.code]();
                }
            }
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
    std::vector<std::unique_ptr<sf::Drawable>>         draw_list_;
    sf::RenderWindow                                   window_;
    std::map<sf::Keyboard::Key, std::function<void()>> key_map_;
};
// =============================================================================
//                                    Tests
// =============================================================================
void DrawTest()
{
    Application app;
    app.InitWindow();
    app.AddDrawable(std::make_unique<sf::RectangleShape>(sf::Vector2f(10, 10)));
    app.AddKey(sf::Keyboard::X,
               [&]()
               {
                   app.AddDrawable(std::make_unique<sf::RectangleShape>(
                       sf::Vector2f(130, 130)));
               });
    app.Run();
}
// =============================================================================
//                                  Test List
// =============================================================================
TEST_LIST = {
    {"DrawTest", DrawTest},
    { NULL,      NULL    }
};
