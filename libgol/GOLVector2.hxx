// ----------------------------------------------------------------------------
// GOLVector2.hxx
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <GOLVector2.hpp>

#include <cmath>

namespace GOL {

// ----------------------------------------------------------------------------
template <class T>
Vector2<T>::Vector2() :
    x( T() ),
    y( T() )
{
}

// ----------------------------------------------------------------------------
template <class T>
Vector2<T>::Vector2( T x, T y ) :
    x(x),
    y(y)
{
}

// ----------------------------------------------------------------------------
template <class T>
Vector2<T>::~Vector2()
{
}

// ----------------------------------------------------------------------------
template <class T>
void Vector2<T>::normalise()
{
    T length = sqrt( x*x + y*y );
    x /= length;
    y /= length;
}

// ----------------------------------------------------------------------------
template <class T>
Vector2<T> Vector2<T>::getNormalised() const
{
    Vector2 ret( *this );
    ret.normalise();
    return ret;
}

// ----------------------------------------------------------------------------
template <class T>
T Vector2<T>::dot() const
{
    return (x*x + y*y );
}

// ----------------------------------------------------------------------------
template <class T>
T Vector2<T>::dot( const Vector2<T>& other ) const
{
    return (x*other.x + y*other.y );
}

// ----------------------------------------------------------------------------
template <class T>
inline bool operator==( const Vector2<T>& lhs, const Vector2<T>& rhs )
{
    return ( lhs.x==rhs.x && lhs.y==rhs.y );
}
template <class T>
inline bool operator!=( const Vector2<T>& lhs, const Vector2<T>& rhs )
{
    return !operator==( lhs, rhs );
}
template <class T>
inline bool operator<( const Vector2<T>& lhs, const Vector2<T>& rhs )
{
    if( lhs.x>rhs.x ) return false;
    if( lhs.y>rhs.y ) return false;
    return true;
}
template <class T>
inline bool operator>( const Vector2<T>& lhs, const Vector2<T>& rhs )
{
    return operator<( rhs, lhs );
}
template <class T>
inline bool operator<=( const Vector2<T>& lhs, const Vector2<T>& rhs )
{
    return !operator>( lhs, rhs );
}
template <class T>
inline bool operator>=( const Vector2<T>& lhs, const Vector2<T>& rhs )
{
    return !operator<( lhs, rhs );
}

// ----------------------------------------------------------------------------
template <class T>
Vector2<T>& Vector2<T>::operator++()
{
    ++x;
    ++y;
    return *this;
}
template <class T>
Vector2<T>& Vector2<T>::operator--()
{
    --x;
    --y;
    return *this;
}
template <class T>
Vector2<T> Vector2<T>::operator++( int )
{
    Vector2<T> tmp( *this );
    operator++();
    return tmp;
}
template <class T>
Vector2<T> Vector2<T>::operator--( int )
{
    Vector2<T> tmp( *this );
    operator--();
    return tmp;
}

// ----------------------------------------------------------------------------
template <class T>
Vector2<T>& Vector2<T>::operator+=( const Vector2<T>& rhs )
{
    x += rhs.x;
    y += rhs.y;
    return *this;
}
template <class T>
Vector2<T>& Vector2<T>::operator-=( const Vector2<T>& rhs )
{
    x -= rhs.x;
    y -= rhs.y;
    return *this;
}

template <class T> inline Vector2<T> operator+( Vector2<T> lhs, const Vector2<T>& rhs ) { lhs += rhs; return lhs; }
template <class T> inline Vector2<T> operator-( Vector2<T> lhs, const Vector2<T>& rhs ) { lhs -= rhs; return lhs; }

} // namespace GOL
