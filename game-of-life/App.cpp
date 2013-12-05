#include <iostream>

#include <App.hpp>
#include <LoopTimer.hpp>
#include <Background.hpp>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

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
    Background background;
    background.generate( sf::Vector2i(800,600) );
    background.setZoomLimits( 0.25, 4.0 );

    // setup loop timer
    LoopTimer loopTimer;
    loopTimer.setFPS( 60 );

    double currentZoom = 1.0, targetZoom = 1.0;
    sf::Vector2i viewPosition(0,0), pinchScrollPosition;
    bool isScrolling = false;

    // run the program as long as the window is open
    while (m_Window.isOpen())
    {

        // update game logic
        while( loopTimer.isTimeToUpdate() )
        {

            // smooth zooming
            currentZoom += (targetZoom-currentZoom)/10.0;
            background.setZoomFactor( currentZoom );
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
                targetZoom += event.mouseWheel.delta/50.0;
                if( targetZoom >= 4.0 ) targetZoom = 4.0;
                if( targetZoom <= 0.25 ) targetZoom = 0.25;
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

                // handle scrolling
                if( isScrolling )
                {
                    viewPosition.x += event.mouseMove.x - pinchScrollPosition.x;
                    viewPosition.y += event.mouseMove.y - pinchScrollPosition.y;
                    pinchScrollPosition.x = event.mouseMove.x;
                    pinchScrollPosition.y = event.mouseMove.y;
                    background.setViewPosition( viewPosition );
                }
            }

        }

        // draw everything
        background.draw( &m_Window );

        // end the current frame
        m_Window.display();
    }
}
