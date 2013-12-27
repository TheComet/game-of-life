#include <iostream>

#include <App.hpp>
#include <LoopTimer.hpp>
#include <Background.hpp>
#include <CellField.hpp>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>

#include <vector>

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

    // list of objects to render every frame
    std::vector<Drawable*> renderList;

    // initialise background
    float zoomLimitMax = 2.0f;
    float zoomLimitMin = 0.25f;
    float zoomSmoothnessFactor = 4.0f;
    Background background;
    background.generate();
    renderList.push_back( &background );

    // initialise cell field
    CellField cellField;
    renderList.push_back( &cellField );

    // set up zooming parameters
    float currentZoom = 1.0f, targetZoom = 1.0f;
    sf::Vector2f viewPosition(0.0f,0.0f);
    sf::Vector2i pinchScrollPosition;
    sf::Vector2i mousePosition;
    bool isScrolling = false;

    // cell timer, keeps track of when to update to next frame
    int cellTimer = 0;

    // set to true when the game is paused
    bool isPaused = true;

    // set up loop timer
    LoopTimer loopTimer;
    loopTimer.setFPS( 60 );

    // run the program as long as the window is open
    while (m_Window.isOpen())
    {

        // update game logic
        while( loopTimer.isTimeToUpdate() )
        {

            // smooth zooming
            float deltaZoom = (currentZoom-targetZoom)/zoomSmoothnessFactor;
            currentZoom -= deltaZoom;

            // adjust view position so zoom occurs under mouse
            viewPosition.x += static_cast<float>(mousePosition.x)*deltaZoom/(currentZoom*currentZoom);
            viewPosition.y += static_cast<float>(mousePosition.y)*deltaZoom/(currentZoom*currentZoom);

            // calculate next frame if time has come
            if( isPaused )
                cellTimer = 0;
            if( ++cellTimer == 5 )
            {
                cellTimer = 0;
                cellField.calculateNextFrame();
            }
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

            // button presses
            if( event.type == sf::Event::KeyPressed )
            {

                // pause/resume with space
                if( event.key.code == sf::Keyboard::Space )
                    isPaused = 1-isPaused;
            }

        }

        // draw everything to render window
        for( std::vector<Drawable*>::iterator it = renderList.begin(); it != renderList.end(); ++it )
            (*it)->draw( &m_Window, sf::Vector2f(800,600), viewPosition, currentZoom );

        // end the current frame
        m_Window.display();
    }
}
