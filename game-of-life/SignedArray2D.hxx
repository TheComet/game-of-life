// --------------------------------------------------------------
// SignedArray2D.hxx
// --------------------------------------------------------------

// --------------------------------------------------------------
// include files

#include <SignedArray2D.hpp>
#include <Exception.hpp>

#include <sstream>
#include <algorithm> // std::reverse

// --------------------------------------------------------------
template <class T>
SignedArray2D<T>::SignedArray2D( void ) :
    m_DefaultContent( T() ),
    m_SizeX(1),
    m_SizeY(1),
    m_OffsetX(0),
    m_OffsetY(0),
    m_Array( std::vector< std::vector<T> >(1) )
{
    m_Array.at(0).push_back( T() ); // make sure array 0,0 has a value
}

// --------------------------------------------------------------
template <class T>
SignedArray2D<T>::SignedArray2D( const T& content ) :
    m_DefaultContent( content ),
    m_SizeX(1),
    m_SizeY(1),
    m_OffsetX(0),
    m_OffsetY(0),
    m_Array( std::vector< std::vector<T> >(1) )
{
    m_Array.at(0).push_back( content ); // make sure array 0,0 has a value
}

// --------------------------------------------------------------
template <class T>
SignedArray2D<T>::SignedArray2D( const SignedArray2D& that ) :
    m_DefaultContent( T() )
{
    *this = that;
}

// --------------------------------------------------------------
template <class T>
SignedArray2D<T>::SignedArray2D( const SignedArray2D& that, const T& content ) :
    m_DefaultContent( content )
{
    *this = that;
}

// --------------------------------------------------------------
template <class T>
SignedArray2D<T>::~SignedArray2D( void )
{
}

// --------------------------------------------------------------
template <class T>
void SignedArray2D<T>::setDefaultContent( const T& content )
{
    m_DefaultContent = content;
}

// --------------------------------------------------------------
template <class T>
const T& SignedArray2D<T>::getDefaultContent( void ) const
{
    return m_DefaultContent;
}

// --------------------------------------------------------------
template <class T>
void SignedArray2D<T>::resize( int x1, int y1, int x2, int y2 )
{

    // boundary check
    if( x2 < x1 || y2 < y1 )
        throw Exception( "[SignedArray2D::resize] Error: Rectangle is fucked up, idiot (coordinates are negative)" );

    std::size_t sizeX = x2-x1+1;
    std::size_t sizeY = y2-y1+1;

    // scale x-dimension up or down
    if( sizeX != m_SizeX )
    {
        m_Array.resize( sizeX );
        while( sizeX > m_SizeX )
        {
            m_Array[m_SizeX].resize( m_SizeY, m_DefaultContent );
            ++m_SizeX;
        }
        m_SizeX = sizeX;
    }

    // scale y-dimension up or down
    if( sizeY != m_SizeY )
    {
        for( typename std::vector< std::vector<T> >::iterator it = m_Array.begin(); it != m_Array.end(); ++it )
        {
            it->resize( sizeY, m_DefaultContent );
        }
        m_SizeY = sizeY;
    }

    // set new offsets
    m_OffsetX = x1;
    m_OffsetY = y1;
}

// --------------------------------------------------------------
template <class T>
void SignedArray2D<T>::mirrorX( void )
{
    if( m_SizeX <= 1 ) return;
    std::reverse( m_Array.begin(), m_Array.end() );
}

// --------------------------------------------------------------
template <class T>
void SignedArray2D<T>::mirrorY( void )
{
    if( !m_SizeX || m_SizeY <= 1 ) return;
    for( typename std::vector< std::vector<T> >::iterator it = m_Array.begin(); it != m_Array.end(); ++it )
        std::reverse( it->begin(), it->end() );
}

// --------------------------------------------------------------
template <class T>
std::size_t SignedArray2D<T>::sizeX( void ) const
{
    return m_SizeX;
}

// --------------------------------------------------------------
template <class T>
std::size_t SignedArray2D<T>::sizeY( void ) const
{
    return m_SizeY;
}

// --------------------------------------------------------------
template <class T>
SignedArray2D<T>& SignedArray2D<T>::operator=( const SignedArray2D<T>& that )
{
    if( &that == this ) return *this;
    m_Array = that.m_Array;
    m_SizeX = that.m_SizeX;
    m_SizeY = that.m_SizeY;
    m_OffsetX = that.m_OffsetX;
    m_OffsetY = that.m_OffsetY;
    return *this;
}

// --------------------------------------------------------------
template <class T>
const T& SignedArray2D<T>::at( int x, int y ) const
{
    return m_Array[x-m_OffsetX][y-m_OffsetY];
}

// --------------------------------------------------------------
template <class T>
T& SignedArray2D<T>::at( int x, int y )
{
    std::size_t memX = x-m_OffsetX;
    std::size_t memY = y-m_OffsetY;
    if( memX >= m_SizeX || memY >= m_SizeY )
    {
        std::stringstream ss; ss << "[SignedArray2D::at] Error: coordinates out of bounds: " << x << "," << y;
        throw Exception( ss.str() );
    }
    return m_Array[memX][memY];
}
