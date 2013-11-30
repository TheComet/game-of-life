#include <App.hpp>
#include <LoopTimer.hpp>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

// ----------------------------------------------------------------------------
App::App()
{
    m_Window = new sf::RenderWindow( sf::VideoMode(800,600), "Game of Life" );
}

// ----------------------------------------------------------------------------
App::~App()
{
    delete m_Window;
}

// ----------------------------------------------------------------------------
void App::go()
{

    // generate background image
    sf::Image backgroundImg;
    backgroundImg.create( 100, 100 );
    for( unsigned int x = 10; x != 100; x += 10 )
        for( unsigned int y = 0; y != 100; ++y )
            backgroundImg.setPixel( x, y, sf::Color(40,40,40) );
    for( unsigned int x = 0; x != 100; ++x )
        for( unsigned int y = 10; y != 100; y += 10 )
            backgroundImg.setPixel( x, y, sf::Color(40,40,40) );
    for( unsigned int n = 0; n != 100; ++n )
    {
        backgroundImg.setPixel( n, 0, sf::Color(128,128,128) );
        backgroundImg.setPixel( 0, n, sf::Color(128,128,128) );
    }

    sf::Texture backgroundTexture;
    backgroundTexture.loadFromImage( backgroundImg, sf::IntRect(0,0,100,100) );

    sf::Sprite backgroundSprite( backgroundTexture );
    backgroundSprite.setPosition( 10, 10 );

    LoopTimer loopTimer;
    loopTimer.setFPS( 60 );

    // run the program as long as the window is open
    while (m_Window->isOpen())
    {

        // update game logic
        while( loopTimer.isTimeToUpdate() )
        {

        }

        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (m_Window->pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                m_Window->close();
        }

        // clear the window with black color
        m_Window->clear(sf::Color::Black);

        m_Window->draw( backgroundSprite );

        // end the current frame
        m_Window->display();
    }
}
