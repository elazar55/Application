#include "acutest.h"
#include <queue>
#include <SFML/Graphics.hpp>

class Application
{
  public:
    Application(int         width  = 800,
                int         height = 600,
                std::string title  = "Title") :
        window_(sf::VideoMode(width, height), title)
    {
    }

    void Run()
    {
        while (window_.isOpen())
        {
            PollEvents();
            Draw();
        }
    }

  private:
    void PollEvents()
    {
        sf::Event event;

        while (window_.pollEvent(event))
            if (event.type == sf::Event::Closed) window_.close();
    }

    void Draw()
    {
        window_.clear();
        window_.display();
    }

    sf::RenderWindow window_;
};

void KeyboardMapTest()
{
    Application app;
    app.Run();
}

TEST_LIST = {
    {"KeyboardMapTest", KeyboardMapTest},
    { NULL,             NULL           }
};
