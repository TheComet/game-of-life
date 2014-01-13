#include <iostream>
#include <cmath>

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
    float zoomLimitMin = 0.125f;
    float zoomSmoothnessFactor = 4.0f;
    Background background;
    background.generate();
    renderList.push_back( &background );

    // initialise cell field
    bool mouseMoveKills = false;
    CellField cellField;
    renderList.push_back( &cellField );

    // set up zooming parameters
    float currentZoom = 1.0f, targetZoom = 1.0f;
    sf::Vector2f viewPosition(0.0f,0.0f);
    sf::Vector2i pinchScrollPosition;
    bool isScrolling = false;

    // mouse states
    sf::Vector2i mousePosition;
    bool mouseButton1 = false;

    // cell timer, keeps track of when to update to next frame
    int cellTimer = 0;

    // speed of simulation
    int simulationSpeed = 5;

    // set to true when the game is paused
    bool isPaused = true;

    // set up loop timer
    LoopTimer loopTimer;
    loopTimer.setFPS( 60 );

    // run the program as long as the window is open
    while (m_Window.isOpen())
    {

        // update game logic
        int maxUpdateLoops = 0;
        while( loopTimer.isTimeToUpdate() )
        {

            // smooth zooming
            float deltaZoom = (currentZoom-targetZoom)/zoomSmoothnessFactor;
            currentZoom -= deltaZoom;

            // adjust view position so zoom occurs under mouse
            viewPosition.x += static_cast<float>(mousePosition.x)*deltaZoom/(currentZoom*currentZoom);
            viewPosition.y += static_cast<float>(mousePosition.y)*deltaZoom/(currentZoom*currentZoom);

            // calculate next frame if time has come
            if( !isPaused && cellTimer++ >= simulationSpeed )
            {
                cellTimer = 0;
                cellField.calculateNextGeneration();
            }

            // limit amount of update loops allowed
            if( ++maxUpdateLoops == 10 )
                break;
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

                // press mouse
                if( event.mouseButton.button == sf::Mouse::Left )
                    mouseButton1 = true;

                // determine if further mouse movement should kill or revive cells
                int cellX = std::floor( (static_cast<float>(event.mouseButton.x)/currentZoom-viewPosition.x)/10.0f );
                int cellY = std::floor( (static_cast<float>(event.mouseButton.y)/currentZoom-viewPosition.y)/10.0f );
                if( cellField.isCellAlive(GOL::Vector2<int>(cellX,cellY)) )
                {
                    mouseMoveKills = true;
                    if( mouseButton1 && isPaused )
                        cellField.removeCell(GOL::Vector2<int>(cellX,cellY));
                }else
                {
                    mouseMoveKills = false;
                    if( mouseButton1 && isPaused )
                        cellField.addCell(GOL::Vector2<int>(cellX,cellY));
                }

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

                // release mouse
                if( event.mouseButton.button == sf::Mouse::Left )
                    mouseButton1 = false;

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

                // handle killing/reviving cells in edit mode
                if( isPaused && mouseButton1 )
                {
                    int cellX = std::floor( (static_cast<float>(event.mouseMove.x)/currentZoom-viewPosition.x)/10.0f );
                    int cellY = std::floor( (static_cast<float>(event.mouseMove.y)/currentZoom-viewPosition.y)/10.0f );
                    if( mouseMoveKills )
                        cellField.removeCell(GOL::Vector2<int>(cellX,cellY));
                    else
                        cellField.addCell(GOL::Vector2<int>(cellX,cellY));
                }

            }

            // button presses
            if( event.type == sf::Event::KeyPressed )
            {

                // pause/resume with space
                if( event.key.code == sf::Keyboard::Space )
                {
                    isPaused = !isPaused;
                }

                // increase simulation speed
                if( event.key.code == sf::Keyboard::Up )
                    if( simulationSpeed > 0 )
                        --simulationSpeed;

                // decrease simulation speed
                if( event.key.code == sf::Keyboard::Down )
                    if( simulationSpeed < 60 )
                        ++simulationSpeed;

                // reset field
                if( event.key.code == sf::Keyboard::Delete )
                    if( isPaused )
                        cellField.reset();
            }

        }

        // clear
        m_Window.clear();

        // draw everything to render window
        for( std::vector<Drawable*>::iterator it = renderList.begin(); it != renderList.end(); ++it )
            (*it)->draw( &m_Window, sf::Vector2f(800,600), viewPosition, currentZoom );

        // end the current frame
        m_Window.display();
    }
}
