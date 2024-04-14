#include <functional>
#include <memory>
#include <SFML/Graphics.hpp>
// =============================================================================
//                                 MyWindow
// =============================================================================
class MyWindow
{
  public:
    // =========================== Public Methods ==============================
    MyWindow()  = default;
    ~MyWindow() = default;
    void InitWindow(int width = 800, int height = 600, std::string title = "");
    void AddDrawable(std::unique_ptr<sf::Drawable> drawable);
    void AddKeyPress(sf::Keyboard::Key key, std::function<void()> func);
    void Run();
    void Close();
  private:
    // =========================== Private Methods =============================
    void PollEvents();
    void Draw();
    // ============================== Variables ================================
    std::vector<std::unique_ptr<sf::Drawable>>         draw_list;
    std::map<sf::Keyboard::Key, std::function<void()>> keypress_map;
    sf::RenderWindow                                   sf_window;
};
// =============================================================================
//                                 InitWindow
// =============================================================================
void MyWindow::InitWindow(int width, int height, std::string title)
{
    sf_window.create(sf::VideoMode(width, height), title);
}
// =============================================================================
//                                 AddDrawable
// =============================================================================
void MyWindow::AddDrawable(std::unique_ptr<sf::Drawable> drawable)
{
    draw_list.push_back(std::move(drawable));
}
// =============================================================================
//                                 AddKeyPress
// =============================================================================
void MyWindow::AddKeyPress(sf::Keyboard::Key key, std::function<void()> func)
{
    keypress_map[key] = func;
}
// =============================================================================
//                                     Run
// =============================================================================
void MyWindow::Run()
{
    while (sf_window.isOpen())
    {
        PollEvents();
        Draw();
    }
}
// =============================================================================
//                                    Close
// =============================================================================
void MyWindow::Close()
{
    sf_window.close();
}
// =============================================================================
//                                 PollEvents
// =============================================================================
void MyWindow::PollEvents()
{
    sf::Event event;

    while (sf_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            Close();
        }
        else if (event.type == sf::Event::KeyPressed)
        {
            if (keypress_map[event.key.code] != nullptr)
            {
                keypress_map[event.key.code]();
            }
        }
    }
}
// =============================================================================
//                                    Draw
// =============================================================================
void MyWindow::Draw()
{
    sf_window.clear();

    for (auto&& i : draw_list)
    {
        sf_window.draw(*i);
    }
    sf_window.display();
}
