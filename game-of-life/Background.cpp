// ----------------------------------------------------------------------------
// include files

#include <SFML/Graphics/RenderTarget.hpp>

#include <Background.hpp>
#include <Exception.hpp>

// ----------------------------------------------------------------------------
Background::Background() :
    m_ZoomFactor(1.0),
    m_ZoomMin(1.0),
    m_ZoomMax(1.0)
{
}

// ----------------------------------------------------------------------------
Background::~Background()
{
}

// ----------------------------------------------------------------------------
void Background::generate()
{
    this->generate( sf::Vector2i(100,100) );
}

// ----------------------------------------------------------------------------
void Background::generate( const sf::Vector2i& viewSize )
{

    // generate 100x100 light-grey grid with 10x10 dark-grey subdivisions
    // and a black background
    sf::Image image;
    image.create( 100, 100 );
    for( unsigned int x = 10; x != 100; x += 10 )
        for( unsigned int y = 0; y != 100; ++y )
            image.setPixel( x, y, sf::Color(40,40,40) );
    for( unsigned int x = 0; x != 100; ++x )
        for( unsigned int y = 10; y != 100; y += 10 )
            image.setPixel( x, y, sf::Color(40,40,40) );
    for( unsigned int n = 0; n != 100; ++n )
    {
        image.setPixel( n, 0, sf::Color(128,128,128) );
        image.setPixel( n, 1, sf::Color(128,128,128) );
        image.setPixel( n, 99, sf::Color(128,128,128) );
        image.setPixel( 0, n, sf::Color(128,128,128) );
        image.setPixel( 1, n, sf::Color(128,128,128) );
        image.setPixel( 99, n, sf::Color(128,128,128) );
    }

    // load texture and sprite from generated image
    m_Texture.loadFromImage( image, sf::IntRect(0,0,100,100) );
    m_Texture.setSmooth(true);
    m_Sprite.setTexture( m_Texture );

    // view size determines how many background sprites need to be tiled
    m_ViewSize = viewSize;
}

// ----------------------------------------------------------------------------
void Background::setViewPosition( const sf::Vector2f& position )
{

    // wrap the position to 100,100 since that's the maximum size of the tiles
    m_Scroll = position;
    while( m_Scroll.x > 100.0f ) m_Scroll.x -= 100.0f;
    while( m_Scroll.y > 100.0f ) m_Scroll.y -= 100.0f;
    while( m_Scroll.x < 0.0f ) m_Scroll.x += 100.0f;
    while( m_Scroll.y < 0.0f ) m_Scroll.y += 100.0f;

    // inverse scroll
    m_Scroll = sf::Vector2f(100,100) - m_Scroll;
}

// ----------------------------------------------------------------------------
void Background::setZoomFactor( double factor )
{

    // zoom and limit
    m_ZoomFactor = factor;
    if( m_ZoomFactor < m_ZoomMin ) m_ZoomFactor = m_ZoomMin;
    if( m_ZoomFactor > m_ZoomMax ) m_ZoomFactor = m_ZoomMax;

}

// ----------------------------------------------------------------------------
void Background::setZoomLimits( double min, double max )
{
    if( min <= 0.0 )
        throw Exception( "[Background::setZoomLimits] Minimum value cannot be 0 or smaller" );
    if( max < min )
        throw Exception( "[Background::setZoomLimits] Maximum zoom factor must be larger than minimum zoom factor" );

    m_ZoomMin = min;
    m_ZoomMax = max;
}

// ----------------------------------------------------------------------------
void Background::draw( sf::RenderTarget* target )
{
    for( float x = 0-(m_Scroll.x*m_ZoomFactor); x <= m_ViewSize.x; x += 100.0f*m_ZoomFactor)
        for( float y = 0-(m_Scroll.y*m_ZoomFactor); y <= m_ViewSize.y; y += 100.0f*m_ZoomFactor)
        {
            m_Sprite.setPosition( x, y );
            m_Sprite.setScale( m_ZoomFactor, m_ZoomFactor );
            target->draw( m_Sprite );
        }
}
