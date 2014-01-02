// ----------------------------------------------------------------------------
// GOLVector2.hpp
// ----------------------------------------------------------------------------

namespace GOL {

template <class T>
class Vector2
{
public:

    /*!
     * @brief Default constructor
     */
    Vector2();

    /*!
     * @brief Constructs a @a Vector2 object with the specified components
     */
    Vector2( T x, T y );

    /*!
     * @brief Default destructor
     */
    ~Vector2();

    /*!
     * @brief Returns the dot product of the vector with itself
     */
    const T dot() const;

    /*!
     * @brief Returns the dot product of the vector with another vector
     */
    const T dot( const Vector2<T>& other ) const;

    /*!
     * @brief Overload comparison operators
     * This is based on the comparison of the dot product
     */
    template <class T_> friend inline bool operator==( const Vector2<T_>& lhs, const Vector2<T_>& rhs );
    template <class T_> friend inline bool operator!=( const Vector2<T_>& lhs, const Vector2<T_>& rhs );
    template <class T_> friend inline bool operator< ( const Vector2<T_>& lhs, const Vector2<T_>& rhs );
    template <class T_> friend inline bool operator> ( const Vector2<T_>& lhs, const Vector2<T_>& rhs );
    template <class T_> friend inline bool operator<=( const Vector2<T_>& lhs, const Vector2<T_>& rhs );
    template <class T_> friend inline bool operator>=( const Vector2<T_>& lhs, const Vector2<T_>& rhs );

    // 2D coordinates
    T x;
    T y;
};

} // namespace GOL
