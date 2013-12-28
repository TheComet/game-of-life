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
    m_BoundaryX1(0),
    m_BoundaryY1(0),
    m_BoundaryX2(1),
    m_BoundaryY2(1)
{

    // initialise cell buffers
    m_CellBuffer[0] = SignedArray2D<Cell>();
    m_CellBuffer[1] = SignedArray2D<Cell>();

    // generate 8x8 image for a single cell
    sf::Image image;
    image.create( 8, 8 );
    for( unsigned int x = 0; x != 8; ++x )
        for( unsigned int y = 0; y != 8; ++y )
            image.setPixel( x, y, sf::Color(255,255,255) );
    m_CellTexture.loadFromImage( image, sf::IntRect(0,0,8,8) );
    m_CellTexture.setSmooth( true );
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
    if( m_CellBuffer[0].at(x,y).isAlive() )
    {
        m_CellBuffer[0].at(x,y).kill();
        m_CellBuffer[1].at(x,y).kill();
    }else
    {
        m_CellBuffer[0].at(x,y).revive();
        m_CellBuffer[1].at(x,y).revive();
    }
}

// ----------------------------------------------------------------------------
bool CellField::isCellAlive( int x, int y )
{

    // out of range
    if( x < m_BoundaryX1+1 || x > m_BoundaryX2-1 || y < m_BoundaryY1+1 || y > m_BoundaryY2-1 )
        return false;

    return m_CellBuffer[0].at(x,y).isAlive();
}

// ----------------------------------------------------------------------------
void CellField::calculateNextFrame()
{

    this->optimumArrayResize();

    // calculate next frame by using the data in the old buffer
    for( int x = m_BoundaryX1+1; x != m_BoundaryX2; ++x )
        for( int y = m_BoundaryY1+1; y != m_BoundaryY2; ++y )
        {

            // count neighbours
            int neighbours = 0;
            for( int nx = x-1; nx != x+2; ++nx )
                for( int ny = y-1; ny != y+2; ++ny )
                    if( m_CellBuffer[0].at(nx,ny).isAlive() )
                        ++neighbours;

            // selected cell is alive
            if( m_CellBuffer[0].at(x,y).isAlive() )
            {

                // counting algorithm above also counts selected cell.
                // resolve this issue
                --neighbours;

                // less than 2 or more than 3 neighbours kills selected cell
                if( neighbours < 2 || neighbours > 3 )
                    m_CellBuffer[1].at(x,y).kill();

            // selected cell is dead
            } else
            {

                // exactly 3 neighbours revives selected cell
                if( neighbours == 3 )
                    m_CellBuffer[1].at(x,y).revive();
            }
        }

    // synchronize buffers
    m_CellBuffer[0] = m_CellBuffer[1];
}

// ----------------------------------------------------------------------------
void CellField::calculatePreviousFrame()
{
    std::cout << "this doesn't twerk yet" << std::endl;
}

// ----------------------------------------------------------------------------
void CellField::reset()
{
    m_BoundaryX1 = 0;
    m_BoundaryY1 = 0;
    m_BoundaryX2 = 1;
    m_BoundaryY1 = 1;
    m_CellBuffer[0] = SignedArray2D<Cell>();
    m_CellBuffer[1] = SignedArray2D<Cell>();
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
                if( m_CellBuffer[0].at(x,y).isAlive() )
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
    m_BoundaryX1 -= 10;
    m_BoundaryY1 -= 10;
    m_BoundaryX2 += 10;
    m_BoundaryY2 += 10;

    m_CellBuffer[0].resize( m_BoundaryX1, m_BoundaryY1, m_BoundaryX2, m_BoundaryY2 );
    m_CellBuffer[1].resize( m_BoundaryX1, m_BoundaryY1, m_BoundaryX2, m_BoundaryY2 );

    std::cout << "array expanded to " << m_BoundaryX1 << "," << m_BoundaryY1 << "," << m_BoundaryX2 << "," << m_BoundaryY2 << std::endl;
}

// ----------------------------------------------------------------------------
void CellField::optimumArrayResize( bool forceResize )
{

    // resize if any cells are touching the outer boundaries of the array
    bool doResize = forceResize;
    for( int n = m_BoundaryX1; n != m_BoundaryX2; ++n )
    {
        if( m_CellBuffer[0].at(n, m_BoundaryY1).isAlive() )
            doResize = true;
        if( m_CellBuffer[0].at(n, m_BoundaryY1+1).isAlive() )
            doResize = true;
        if( m_CellBuffer[0].at(n, m_BoundaryY2).isAlive() )
            doResize = true;
        if( m_CellBuffer[0].at(n, m_BoundaryY2-1).isAlive() )
            doResize = true;
    }
    for( int n = m_BoundaryY1; n != m_BoundaryY2; ++n )
    {
        if( m_CellBuffer[0].at(m_BoundaryX1, n).isAlive() )
            doResize = true;
        if( m_CellBuffer[0].at(m_BoundaryX1+1, n).isAlive() )
            doResize = true;
        if( m_CellBuffer[0].at(m_BoundaryX2, n).isAlive() )
            doResize = true;
        if( m_CellBuffer[0].at(m_BoundaryX2-1, n).isAlive() )
            doResize = true;
    }

    // only check for optimum size if a resize is necessary
    if( doResize )
    {

        // reduce boundaries until a live cell is found
        while( m_BoundaryY1 < m_BoundaryY2 && m_BoundaryX1 < m_BoundaryX2 )
        {
            bool found = true;

            // reduce bottom boundary
            bool contract = true;
            for( int n = m_BoundaryX1; n != m_BoundaryX2; ++n )
                if( m_CellBuffer[0].at(n,m_BoundaryY1).isAlive() || m_CellBuffer[0].at(n,m_BoundaryY1+1).isAlive() )
                {
                    contract = false;
                    break;
                }
            if( contract )
            {
                ++m_BoundaryY1;
                found = false;
            }

            // reduce top boundary
            contract = true;
            for( int n = m_BoundaryX1; n != m_BoundaryX2; ++n )
                if( m_CellBuffer[0].at(n,m_BoundaryY2).isAlive() || m_CellBuffer[0].at(n,m_BoundaryY2-1).isAlive() )
                {
                    contract = false;
                    break;
                }
            if( contract )
            {
                --m_BoundaryY2;
                found = false;
            }

            // reduce left boundary
            contract = true;
            for( int n = m_BoundaryY1; n != m_BoundaryY2; ++n)
                if( m_CellBuffer[0].at(m_BoundaryX1,n).isAlive() || m_CellBuffer[0].at(m_BoundaryX1+1,n).isAlive() )
                {
                    contract = false;
                    break;
                }
            if( contract )
            {
                ++m_BoundaryX1;
                found = false;
            }

            // reduce right boundary
            contract = true;
            for( int n = m_BoundaryY1; n != m_BoundaryY2; ++ n)
                if( m_CellBuffer[0].at(m_BoundaryX2,n).isAlive() || m_CellBuffer[0].at(m_BoundaryX2-1,n).isAlive() )
                {
                    contract = false;
                    break;
                }
            if( contract )
            {
                --m_BoundaryX2;
                found = false;
            }

            // cells were found on all four sides
            if( found )
                break;
        }

        // finally, expand array
        this->expandArray( m_BoundaryX1, m_BoundaryY1 );
    }
}
