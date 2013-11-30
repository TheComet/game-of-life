namespace sf {
    class RenderWindow;
}

class App
{
public:

    App();
    ~App();
    void go();
private:

    sf::RenderWindow* m_Window;
};
