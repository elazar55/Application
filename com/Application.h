#include <functional>
#include <memory>
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

    // ============================ Add Drawable ===============================
    void AddDrawable(std::unique_ptr<sf::Drawable> drawable)
    {
        draw_list_.push_back(std::move(drawable));
    }

    // =========================== Add Key Press ===============================
    void AddKeyPress(sf::Keyboard::Key key, std::function<void()> func)
    {
        keypress_map_[key] = func;
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

    // ================================ Close ==================================
    void Close()
    {
        window_.close();
        // Cleanup resources...
    }
  private:
    // ============================ Poll Events ================================
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
    std::map<sf::Keyboard::Key, std::function<void()>> keypress_map_;
    sf::RenderWindow                                   window_;
};
