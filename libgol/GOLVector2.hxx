// ----------------------------------------------------------------------------
// GOLVector2.hxx
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <GOLVector2.hpp>

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
const T Vector2<T>::dot() const
{
    return (x*x + y*y );
}

// ----------------------------------------------------------------------------
template <class T>
const T Vector2<T>::dot( const Vector2<T>& other ) const
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

} // namespace GOL
