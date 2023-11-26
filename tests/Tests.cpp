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
        key_map_.emplace(sf::Keyboard::Escape,
                         std::bind(&sf::RenderWindow::close, &this->window_));
    }
    // ============================= Assign Key ================================
    void SwapKey(sf::Keyboard::Key old_key, sf::Keyboard::Key new_key)
    {
        auto func         = key_map_[old_key];
        key_map_[old_key] = key_map_[new_key];
        key_map_[new_key] = func;
    }
    // ============================ Add Drawable ===============================
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
  private:
    // ============================ Poll Events ================================
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
    std::map<sf::Keyboard::Key, std::function<void()>> key_map_;
    sf::RenderWindow                                   window_;
};
// =============================================================================
//                                    Tests
// =============================================================================
void AddKeyTest()
{
    Application app;
    app.InitWindow();
    app.SwapKey(sf::Keyboard::X, sf::Keyboard::Escape);
    app.Run();
}
// =============================================================================
void DrawTest()
{
    Application app;
    app.InitWindow();
    app.AddDrawable(std::make_unique<sf::RectangleShape>(sf::Vector2f(10, 10)));
    app.Run();
}
// =============================================================================
//                                  Test List
// =============================================================================
TEST_LIST = {
  // { "DrawTest",   DrawTest   },
    {"AddKeyTest", AddKeyTest},
    { NULL,        NULL      }
};
