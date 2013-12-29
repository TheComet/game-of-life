// ----------------------------------------------------------------------------
// include files

#include <SFML/Graphics/RenderTarget.hpp>

#include <Background.hpp>
#include <Exception.hpp>

// ----------------------------------------------------------------------------
Background::Background()
{
}

// ----------------------------------------------------------------------------
Background::~Background()
{
}

// ----------------------------------------------------------------------------
void Background::generate()
{

    // generate 100x100 light-grey grid with 10x10 dark-grey subdivisions
    // and a black background
    sf::Image image;
    image.create( 100, 100 );
    for( unsigned int n = 0; n != 100; ++n )
    {
        image.setPixel( n, 0, sf::Color(128,128,128) );
        image.setPixel( n, 1, sf::Color(128,128,128) );
        image.setPixel( n, 99, sf::Color(128,128,128) );
        image.setPixel( 0, n, sf::Color(128,128,128) );
        image.setPixel( 1, n, sf::Color(128,128,128) );
        image.setPixel( 99, n, sf::Color(128,128,128) );
    }

    // get texture for zoomed out view
    m_ZoomedOutTexture.loadFromImage( image, sf::IntRect(0,0,100,100) );
    m_ZoomedOutTexture.setSmooth( true );

    // add subdivisions for zoomed in texture
    for( unsigned int x = 10; x != 100; x += 10 )
        for( unsigned int y = 0; y != 100; ++y )
            image.setPixel( x, y, sf::Color(40,40,40) );
    for( unsigned int x = 0; x != 100; ++x )
        for( unsigned int y = 10; y != 100; y += 10 )
            image.setPixel( x, y, sf::Color(40,40,40) );

    // load texture and sprite from generated image
    m_Texture.loadFromImage( image, sf::IntRect(0,0,100,100) );
    m_Texture.setSmooth(true);
}

// ----------------------------------------------------------------------------
void Background::draw( sf::RenderTarget* target, sf::Vector2f viewSize, sf::Vector2f viewPosition, float zoomFactor )
{

    // wrap view position to receive a value between 0 and 100 (because each
    // tiled image is 100x100). Scroll needs to be inversed, because background
    // moves against the view position
    sf::Vector2f scroll = viewPosition;
    while( scroll.x > 100.0f ) scroll.x -= 100.0f;
    while( scroll.y > 100.0f ) scroll.y -= 100.0f;
    while( scroll.x < 0.0f ) scroll.x += 100.0f;
    while( scroll.y < 0.0f ) scroll.y += 100.0f;
    scroll = sf::Vector2f(100,100) - scroll;

    // set zoomed in or zoomed out texture, depending on zoom factor
    if( zoomFactor < 0.5 )
        m_Sprite.setTexture( m_ZoomedOutTexture );
    else
        m_Sprite.setTexture( m_Texture );

    // draw tiles to screen if zoom factor is large enough, otherwise don't (for black)
    if( zoomFactor > 0.15 )
    for( float x = 0-(scroll.x*zoomFactor); x <= viewSize.x; x += 100.0f*zoomFactor)
        for( float y = 0-(scroll.y*zoomFactor); y <= viewSize.y; y += 100.0f*zoomFactor)
        {
            m_Sprite.setPosition( x, y );
            m_Sprite.setScale( zoomFactor, zoomFactor );
            target->draw( m_Sprite );
        }
}
