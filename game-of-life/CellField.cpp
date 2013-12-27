// ----------------------------------------------------------------------------
// CellField.cpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <CellField.hpp>
#include <SFML/System/Vector2.hpp>

// ----------------------------------------------------------------------------
CellField::CellField()
{
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

void CellField::draw( sf::RenderTarget* target, sf::Vector2f viewSize, sf::Vector2f viewPosition, float zoomFactor )
{

}
