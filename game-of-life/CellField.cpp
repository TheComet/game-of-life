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
    m_Cells( Cell() ), // fill array with dead cells by default
    m_BoundaryX1(0),
    m_BoundaryY1(0),
    m_BoundaryX2(1),
    m_BoundaryY2(1)
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
void CellField::toggleCell( int x, int y )
{

    // resize array if necessary
    if( x < m_BoundaryX1+1 || x > m_BoundaryX2-1 || y < m_BoundaryY1+1 || y > m_BoundaryY2-1 )
        this->expandArray( x, y );

    // toggle
    if( m_Cells.at(x,y).isAlive() )
        m_Cells.at(x,y).kill();
    else
        m_Cells.at(x,y).revive();
}

// ----------------------------------------------------------------------------
bool CellField::isCellAlive( int x, int y )
{

    // out of range
    if( x < m_BoundaryX1+1 || x > m_BoundaryX2-1 || y < m_BoundaryY1+1 || y > m_BoundaryY2-1 )
        return false;

    return m_Cells.at(x,y).isAlive();
}

// ----------------------------------------------------------------------------
void CellField::calculateNextFrame()
{

    // resize if any cells are touching the outer boundaries of the array
    bool doResize = false;
    for( int n = m_BoundaryX1; n != m_BoundaryX2; ++n )
    {
        if( m_Cells.at(n,m_BoundaryY1).isAlive() )
            doResize = true;
        if( m_Cells.at(n,m_BoundaryY2).isAlive() )
            doResize = true;
    }
    for( int n = m_BoundaryY1; n != m_BoundaryY2; ++n )
    {
        if( m_Cells.at(m_BoundaryX1, n).isAlive() )
            doResize = true;
        if( m_Cells.at(m_BoundaryX2, n).isAlive() )
            doResize = true;
    }
    if( doResize )
        this->expandArray( m_BoundaryX1, m_BoundaryY1 );

    // calculate next frame with the help of a temp buffer
    SignedArray2D<Cell> tempCellField( m_Cells );
    for( int x = m_BoundaryX1+1; x != m_BoundaryX2; ++x )
        for( int y = m_BoundaryY1+1; y != m_BoundaryY2; ++y )
        {

            // count neighbours
            int neighbours = 0;
            for( int nx = x-1; nx != x+2; ++nx )
                for( int ny = y-1; ny != y+2; ++ny )
                    if( tempCellField.at(nx,ny).isAlive() )
                        ++neighbours;

            // selected cell is alive
            if( tempCellField.at(x,y).isAlive() )
            {

                // counting algorithm above also counts selected cell.
                // resolve this issue
                --neighbours;

                // less than 2 or more than 3 neighbours kills selected cell
                if( neighbours < 2 || neighbours > 3 )
                    m_Cells.at(x,y).kill();

            // selected cell is dead
            } else
            {

                // exactly 3 neighbours revives selected cell
                if( neighbours == 3 )
                    m_Cells.at(x,y).revive();
            }
        }

}

// ----------------------------------------------------------------------------
void CellField::calculatePreviousFrame()
{
    std::cout << "this doesn't twerk yet" << std::endl;
}

// ----------------------------------------------------------------------------
sf::Vector2u CellField::getSize()
{
    return sf::Vector2u( m_BoundaryX2-m_BoundaryX1, m_BoundaryY2-m_BoundaryY1 );
}

// ----------------------------------------------------------------------------
std::size_t CellField::getSizeX()
{
    return m_BoundaryX2-m_BoundaryX1;
}

// ----------------------------------------------------------------------------
std::size_t CellField::getSizeY()
{
    return m_BoundaryY2-m_BoundaryY1;
}

// ----------------------------------------------------------------------------
void CellField::draw( sf::RenderTarget* target, sf::Vector2f viewSize, sf::Vector2f viewPosition, float zoomFactor )
{

    for( int x = m_BoundaryX1; x != m_BoundaryX2; ++x )
        for( int y = m_BoundaryY1; y != m_BoundaryY2; ++y )
            if( (viewPosition.x+static_cast<float>(x)*10.0f)*zoomFactor >= -10.0f &&
                (viewPosition.y+static_cast<float>(y)*10.0f)*zoomFactor >= -10.0f &&
                (viewPosition.x+static_cast<float>(x)*10.0f)*zoomFactor <= viewSize.x &&
                (viewPosition.y+static_cast<float>(y)*10.0f)*zoomFactor <= viewSize.y )
                if( m_Cells.at(x,y).isAlive() )
                {
                    m_CellSprite.setPosition( ((x*10.0f)+viewPosition.x+1.0f)*zoomFactor, ((y*10.0f)+viewPosition.y+1.0f)*zoomFactor ); // shift by 1,1 (1.0*zoomFactor)
                    m_CellSprite.setScale( zoomFactor, zoomFactor );
                    target->draw( m_CellSprite );
                }
}

// ----------------------------------------------------------------------------
void CellField::expandArray( int x, int y )
{
    if( x < m_BoundaryX1 ) m_BoundaryX1 = x;
    if( x > m_BoundaryX2 ) m_BoundaryX2 = x;
    if( y < m_BoundaryY1 ) m_BoundaryY1 = y;
    if( y > m_BoundaryY2 ) m_BoundaryY2 = y;
    m_BoundaryY1 -= 10;
    m_BoundaryX1 -= 10;
    m_BoundaryY2 += 10;
    m_BoundaryX2 += 10;
    m_Cells.resize( m_BoundaryX1, m_BoundaryY1, m_BoundaryX2, m_BoundaryY2 );
}

// ----------------------------------------------------------------------------
void CellField::optimumArrayResize()
{
    // TODO smart resizing
}
