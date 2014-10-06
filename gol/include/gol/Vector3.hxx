// ----------------------------------------------------------------------------
// GOLVector3.hxx
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <GOLVector3.hpp>

#include <cmath>

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
void Vector3<T>::normalise()
{
    T length = sqrt( x*x + y*y + z*z );
    x /= length;
    y /= length;
    z /= length;
}

// ----------------------------------------------------------------------------
template <class T>
Vector3<T> Vector3<T>::getNormalised() const
{
    Vector3 ret( *this );
    ret.normalise();
    return ret;
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
void Vector3<T>::cross( const Vector3<T>& that )
{
    T temp1 = x;
    T temp2 = y;
    x = y*that.z - z*that.y;
    y = z*that.x - temp1*that.z;
    z = temp1*that.y - temp2*that.x;
}

// ----------------------------------------------------------------------------
template <class T>
Vector3<T> Vector3<T>::getCross( const Vector3<T>& that ) const
{
    Vector3 ret( *this );
    ret.cross( that );
    return ret;
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
    if( lhs.x < rhs.x ) return true;
    if( lhs.x > rhs.x ) return false;
    if( lhs.y < rhs.y ) return true;
    if( lhs.y > rhs.y ) return false;
    return lhs.z < rhs.z;
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

// ----------------------------------------------------------------------------
template <class T>
Vector3<T>& Vector3<T>::operator++()
{
    ++x;
    ++y;
    ++z;
    return *this;
}
template <class T>
Vector3<T>& Vector3<T>::operator--()
{
    --x;
    --y;
    --z;
    return *this;
}
template <class T>
Vector3<T> Vector3<T>::operator++( int )
{
    Vector3<T> tmp( *this );
    operator++();
    return tmp;
}
template <class T>
Vector3<T> Vector3<T>::operator--( int )
{
    Vector3<T> tmp( *this );
    operator--();
    return tmp;
}

// ----------------------------------------------------------------------------
template <class T>
Vector3<T>& Vector3<T>::operator+=( const Vector3<T>& rhs )
{
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    return *this;
}
template <class T>
Vector3<T>& Vector3<T>::operator-=( const Vector3<T>& rhs )
{
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    return *this;
}

template <class T> inline Vector3<T> operator+( Vector3<T> lhs, const Vector3<T>& rhs ) { lhs += rhs; return lhs; }
template <class T> inline Vector3<T> operator-( Vector3<T> lhs, const Vector3<T>& rhs ) { lhs -= rhs; return lhs; }

} // namespace GOL
