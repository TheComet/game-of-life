#include <iostream>

#include <App.hpp>
#include <LoopTimer.hpp>
#include <Background.hpp>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

#include <vector>
class Cell
{
public:
    Cell() : m_State(false) {}
    ~Cell() {}

    void kill() { m_State = false; }
    void revive() { m_State = true; }

    bool isAlive() { return m_State; }

private:
    bool m_State;
    sf::Vector2i m_Coordinate;
};

class CellMap
{
public:
    CellMap() {}
    ~CellMap() {}

private:
    std::vector<Cell> m_CellList;
};

template <class T>
class Array2D
{
public:

    Array2D() {}

private:
    std::vector<T> m_Data;
};

// ----------------------------------------------------------------------------
App::App() :
    m_Window( sf::VideoMode(800,600), "Game of Life" )
{
}

// ----------------------------------------------------------------------------
App::~App()
{
}

// ----------------------------------------------------------------------------
void App::go()
{

    // initialise background
    float zoomLimitMax = 2.0f;
    float zoomLimitMin = 0.25f;
    float zoomSmoothnessFactor = 4.0f;
    Background background;
    background.generate( sf::Vector2i(800,600) );
    background.setZoomLimits( zoomLimitMin, zoomLimitMax );

    // setup loop timer
    LoopTimer loopTimer;
    loopTimer.setFPS( 60 );

    float currentZoom = 1.0f, targetZoom = 1.0f;
    sf::Vector2f viewPosition(0.0f,0.0f);
    sf::Vector2i pinchScrollPosition;
    sf::Vector2i mousePosition;
    bool isScrolling = false;

    // run the program as long as the window is open
    while (m_Window.isOpen())
    {

        // update game logic
        while( loopTimer.isTimeToUpdate() )
        {

            // smooth zooming
            float deltaZoom = (currentZoom-targetZoom)/zoomSmoothnessFactor;
            currentZoom -= deltaZoom;
            background.setZoomFactor( currentZoom );

            // adjust view position so zoom occurs under mouse
            viewPosition.x += static_cast<float>(mousePosition.x)*deltaZoom/(currentZoom*currentZoom);
            viewPosition.y += static_cast<float>(mousePosition.y)*deltaZoom/(currentZoom*currentZoom);
            background.setViewPosition( viewPosition );
        }

        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while( m_Window.pollEvent(event) )
        {

            // "close requested" event: close the window
            if( event.type == sf::Event::Closed )
                m_Window.close();

            // handle zooming
            if( event.type == sf::Event::MouseWheelMoved )
            {
                targetZoom += event.mouseWheel.delta/50.0f;
                if( targetZoom >= zoomLimitMax ) targetZoom = zoomLimitMax;
                if( targetZoom <= zoomLimitMin ) targetZoom = zoomLimitMin;
            }

            // mouse button pressed
            if( event.type == sf::Event::MouseButtonPressed )
            {

                // begin scrolling
                if( event.mouseButton.button == sf::Mouse::Right )
                {
                    isScrolling = true;
                    pinchScrollPosition.x = event.mouseButton.x;
                    pinchScrollPosition.y = event.mouseButton.y;
                }
            }

            // mouse button released
            if( event.type == sf::Event::MouseButtonReleased )
            {

                // end scrolling
                if( event.mouseButton.button == sf::Mouse::Right )
                    isScrolling = false;
            }

            // mouse movement
            if( event.type == sf::Event::MouseMoved )
            {

                // set mouse position
                mousePosition.x = event.mouseMove.x;
                mousePosition.y = event.mouseMove.y;

                // handle scrolling
                if( isScrolling )
                {
                    viewPosition.x += static_cast<float>(event.mouseMove.x - pinchScrollPosition.x)/currentZoom;
                    viewPosition.y += static_cast<float>(event.mouseMove.y - pinchScrollPosition.y)/currentZoom;
                    pinchScrollPosition.x = event.mouseMove.x;
                    pinchScrollPosition.y = event.mouseMove.y;
                }
            }

        }

        // draw everything
        background.draw( &m_Window );

        // end the current frame
        m_Window.display();
    }
}
