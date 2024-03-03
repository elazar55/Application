#include <functional>
#include <memory>
#include <SFML/Graphics.hpp>

class Application
{
  public:
    Application() = default;
    void InitWindow(int         width  = 800,
                    int         height = 600,
                    std::string title  = "Title")
    {
        window_.create(sf::VideoMode(width, height), title);
    }
    void AddDrawable(std::unique_ptr<sf::Drawable> drawable)
    {
        draw_list_.push_back(std::move(drawable));
    }
    void AddKeyPress(sf::Keyboard::Key key, std::function<void()> func)
    {
        keypress_map_[key] = func;
    }
    void Run()
    {
        while (window_.isOpen())
        {
            PollEvents();
            Draw();
        }
    }
    void Close()
    {
        window_.close();
    }
  private:
    void PollEvents()
    {
        sf::Event event;

        while (window_.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) Close();
            if (event.type == sf::Event::KeyPressed)
            {
                if (keypress_map_[event.key.code] != nullptr)
                {
                    keypress_map_[event.key.code]();
                }
            }
        }
    }
    void Draw()
    {
        window_.clear();
        for (auto&& i : draw_list_)
        {
            window_.draw(*i);
        }
        window_.display();
    }
    std::vector<std::unique_ptr<sf::Drawable>>         draw_list_;
    std::map<sf::Keyboard::Key, std::function<void()>> keypress_map_;
    sf::RenderWindow                                   window_;
};
