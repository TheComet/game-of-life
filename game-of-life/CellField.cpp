// ----------------------------------------------------------------------------
// CellField.cpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <CellField.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

// ----------------------------------------------------------------------------
CellField::CellField() :
    m_Cells( Cell() ) // fill array with dead cells by default
{

    // generate 8x8 image for a single cell
    sf::Image image;
    image.create( 8, 8 );
    for( unsigned int x = 0; x != 8; ++x )
        for( unsigned int y = 0; y != 8; ++y )
            image.setPixel( x, y, sf::Color(255,255,255) );
    m_CellTexture.loadFromImage( image, sf::IntRect(0,0,8,8) );
    m_CellSprite.setTexture( m_CellTexture );
}

// ----------------------------------------------------------------------------
CellField::~CellField()
{
}

// ----------------------------------------------------------------------------
void CellField::calculateNextFrame()
{
}

// ----------------------------------------------------------------------------
void CellField::calculatePreviousFrame()
{
}

// ----------------------------------------------------------------------------
sf::Vector2u CellField::getSize()
{
    return sf::Vector2u( m_Cells.sizeX(), m_Cells.sizeY() );
}

// ----------------------------------------------------------------------------
std::size_t CellField::getSizeX()
{
    return m_Cells.sizeX();
}

// ----------------------------------------------------------------------------
std::size_t CellField::getSizeY()
{
    return m_Cells.sizeY();
}

// ----------------------------------------------------------------------------
void CellField::draw( sf::RenderTarget* target, sf::Vector2f viewSize, sf::Vector2f viewPosition, float zoomFactor )
{

    for( std::size_t x = 0; x != m_Cells.sizeX(); ++x )
        for( std::size_t y = 0; y != m_Cells.sizeY(); ++y )
            if( viewPosition.x-static_cast<float>(x) >= -10.0f &&
                viewPosition.y-static_cast<float>(y) >= -10.0f &&
                viewPosition.x-static_cast<float>(x) <= viewSize.x &&
                viewPosition.y-static_cast<float>(y) <= viewSize.y )
                if( m_Cells.at(x,y).isAlive() )
                {
                    m_CellSprite.setPosition( (x+viewPosition.x+1.0f)*zoomFactor, (y+viewPosition.y+1.0f)*zoomFactor ); // shift by 1,1 (1.0*zoomFactor)
                    m_CellSprite.setScale( zoomFactor, zoomFactor );
                    target->draw( m_CellSprite );
                }
}
