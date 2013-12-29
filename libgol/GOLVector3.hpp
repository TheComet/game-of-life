// ----------------------------------------------------------------------------
// GOLVector3.hpp
// ----------------------------------------------------------------------------

namespace GOL {

template <class T>
class Vector3
{
public:

    /*!
     * @brief Default constructor
     */
    Vector3();

    /*!
     * @brief Constructs a @a Vector3 object with the specified components
     */
    Vector3( T x, T y, T z );

    /*!
     * @brief Default destructor
     */
    ~Vector3();

    /*!
     * @brief Returns the dot product of the vector with itself
     */
    const T dot() const;

    /*!
     * @brief Returns the dot product of the vector with another vector
     */
    const T dot( const Vector3<T>& other ) const;

    /*!
     * @brief Overload comparison operators
     * This is based on the comparison of the dot product
     */
    template <class T_> friend inline bool operator==( const Vector3<T_>& lhs, const Vector3<T_>& rhs );
    template <class T_> friend inline bool operator!=( const Vector3<T_>& lhs, const Vector3<T_>& rhs );
    template <class T_> friend inline bool operator< ( const Vector3<T_>& lhs, const Vector3<T_>& rhs );
    template <class T_> friend inline bool operator> ( const Vector3<T_>& lhs, const Vector3<T_>& rhs );
    template <class T_> friend inline bool operator<=( const Vector3<T_>& lhs, const Vector3<T_>& rhs );
    template <class T_> friend inline bool operator>=( const Vector3<T_>& lhs, const Vector3<T_>& rhs );

    // 3D coordinates
    T x;
    T y;
    T z;
};

} // namespace GOL
