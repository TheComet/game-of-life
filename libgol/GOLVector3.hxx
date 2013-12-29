// ----------------------------------------------------------------------------
// GOLVector3.hxx
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <GOLVector3.hpp>

namespace GOL {

// ----------------------------------------------------------------------------
template <class T>
Vector3<T>::Vector3() :
    x( T() ),
    y( T() ),
    z( T() )
{
}

// ----------------------------------------------------------------------------
template <class T>
Vector3<T>::Vector3( T x, T y, T z ) :
    x(x),
    y(y),
    z(z)
{
}

// ----------------------------------------------------------------------------
template <class T>
Vector3<T>::~Vector3()
{
}

// ----------------------------------------------------------------------------
template <class T>
const T Vector3<T>::dot() const
{
    return (x*x + y*y + z*z);
}

// ----------------------------------------------------------------------------
template <class T>
const T Vector3<T>::dot( const Vector3<T>& other ) const
{
    return (x*other.x + y*other.y + z*other.z);
}

// ----------------------------------------------------------------------------
template <class T>
inline bool operator==( const Vector3<T>& lhs, const Vector3<T>& rhs )
{
    return ( lhs.x==rhs.x && lhs.y==rhs.y && lhs.z==rhs.z );
}
template <class T>
inline bool operator!=( const Vector3<T>& lhs, const Vector3<T>& rhs )
{
    return !operator==( lhs, rhs );
}
template <class T>
inline bool operator<( const Vector3<T>& lhs, const Vector3<T>& rhs )
{
    return ( lhs.dot() < rhs.dot() );
}
template <class T>
inline bool operator>( const Vector3<T>& lhs, const Vector3<T>& rhs )
{
    return operator<( rhs, lhs );
}
template <class T>
inline bool operator<=( const Vector3<T>& lhs, const Vector3<T>& rhs )
{
    return !operator>( lhs, rhs );
}
template <class T>
inline bool operator>=( const Vector3<T>& lhs, const Vector3<T>& rhs )
{
    return !operator<( lhs, rhs );
}

} // namespace GOL
