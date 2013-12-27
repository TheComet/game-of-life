// --------------------------------------------------------------
// SignedArray2D.hxx
// --------------------------------------------------------------

// --------------------------------------------------------------
// include files

#include <SignedArray2D.hpp>
#include <Exception.hpp>

#include <sstream>

// --------------------------------------------------------------
template <class T>
SignedArray2D<T>::SignedArray2D( void ) :
    m_DefaultContent( T() ),
    m_SizeX(1),
    m_SizeY(1),
    m_OffsetX(0),
    m_OffsetY(0),
    m_Data(0)
{
    m_Data = new T[1];
    *m_Data = m_DefaultContent;
}

// --------------------------------------------------------------
template <class T>
SignedArray2D<T>::SignedArray2D( const T& content ) :
    m_DefaultContent( content ),
    m_SizeX(1),
    m_SizeY(1),
    m_OffsetX(0),
    m_OffsetY(0),
    m_Data(0)
{
    m_Data = new T[1];
    *m_Data = m_DefaultContent;
}

// --------------------------------------------------------------
template <class T>
SignedArray2D<T>::SignedArray2D( const SignedArray2D& that ) :
    m_DefaultContent( T() ),
    m_Data(0)
{
    *this = that;
}

// --------------------------------------------------------------
template <class T>
SignedArray2D<T>::SignedArray2D( const SignedArray2D& that, const T& content ) :
    m_DefaultContent( content ),
    m_Data(0)
{
    *this = that;
}

// --------------------------------------------------------------
template <class T>
SignedArray2D<T>::~SignedArray2D( void )
{
    delete[] m_Data;
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
    {
        std::stringstream ss; ss << "[SignedArray2D::resize] Error: Rectangle is fucked up, idiot\
 (coordinates are negative: x1:" << x1 << " y1:" << y1 << " x2:" << x2 << " y2:" << y2;
        throw Exception( ss.str() );
    }

    // new sizes
    std::size_t sizeX = x2-x1+1;
    std::size_t sizeY = y2-y1+1;
    std::size_t size = sizeX*sizeY;

    // re-organize and copy current data into new array, and fill with default
    // content where necessary
    T* temp = new T[size];
    for( std::size_t x = 0; x != sizeX; ++x )
        for( std::size_t y = 0; y != sizeY; ++y )
            if( static_cast<int>(x)-m_OffsetX+x1 >= 0 && // casts are necessary because the result of an arithmetic
                                                         // calculation with an int and a size_t results in a size_t
                                                         // for some reason
                static_cast<int>(y)-m_OffsetY+y1 >= 0 &&
                static_cast<int>(x)-m_OffsetX+x1 < static_cast<int>(m_SizeX) &&
                static_cast<int>(y)-m_OffsetY+y1 < static_cast<int>(m_SizeY))
                temp[x*sizeY+y] = m_Data[(x-m_OffsetX+x1)*m_SizeY+y-m_OffsetY+y1];
            else
                temp[x*sizeY+y] = m_DefaultContent;
    if( m_Data )
        delete[] m_Data;
    m_Data = temp;

    // set new offsets and size
    m_SizeX = sizeX;
    m_SizeY = sizeY;
    m_OffsetX = x1;
    m_OffsetY = y1;
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

    // re-allocate with same size and copy data across
    std::size_t size = that.m_SizeX*that.m_SizeY;
    T* temp = new T[size];
    for( std::size_t i = 0; i != size; ++i )
        *(temp+i) = *(that.m_Data+i);
    if( m_Data )
        delete[] m_Data;
    m_Data = temp;

    // other member data
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
    std::size_t memX = x-m_OffsetX;
    std::size_t memY = y-m_OffsetY;
    if( memX >= m_SizeX || memY >= m_SizeY )
    {
        std::stringstream ss; ss << "[SignedArray2D::at] Error: coordinates out of bounds: " << x << "," << y;
        throw Exception( ss.str() );
    }
    return m_Data[memX*m_SizeY+memY];
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
    return m_Data[memX*m_SizeY+memY];
}
