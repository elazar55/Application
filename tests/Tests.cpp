#include "acutest.h"
#include <iostream>
#include <queue>
#include <SFML/Graphics.hpp>
/* ========================================================================== */
/*                              Class Application                             */
/* ========================================================================== */
class Application
{
  public:
    Application() = default;
    /* ====================================================================== */
    /*                               InitWindow                               */
    /* ====================================================================== */
    void InitWindow(int         width  = 800,
                    int         height = 600,
                    std::string title  = "Title")
    {
        window_.create(sf::VideoMode(width, height), title);
    }
    /* ====================================================================== */
    /*                                   Run                                  */
    /* ====================================================================== */
    void Run()
    {
        while (window_.isOpen())
        {
            PollEvents();
            Draw();
        }
    }
  private:
    /* ====================================================================== */
    /*                               PollEvents                               */
    /* ====================================================================== */
    void PollEvents()
    {
        sf::Event event;

        while (window_.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window_.close();
            if (event.key.code == sf::Keyboard::Escape) window_.close();
        }
    }
    /* ====================================================================== */
    /*                                  Draw                                  */
    /* ====================================================================== */
    void Draw()
    {
        window_.clear();
        for (auto&& i : drawList)
        {
            window_.draw(i);
        }
        window_.display();
    }
    /* ====================================================================== */
    /*                          Member Fields                                 */
    /* ====================================================================== */
    std::vector<sf::Drawable> drawList;
    sf::RenderWindow          window_;
};
/* ========================================================================== */
/*                                    Tests                                   */
/* ========================================================================== */
void KeyboardMapTest()
{
    Application app;
    app.InitWindow();
    app.Run();
}
/* ========================================================================== */
/*                                  Test List                                 */
/* ========================================================================== */
TEST_LIST = {
    {"KeyboardMapTest", KeyboardMapTest},
    { NULL,             NULL           }
};
