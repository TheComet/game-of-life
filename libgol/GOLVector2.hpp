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
     * @brief Normalises the vector
     */
    void normalise();

    /*!
     * @brief Returns a new normalised version of the object without affecting the original
     */
    Vector2 getNormalised() const;

    /*!
     * @brief Returns the dot product of the vector with itself
     */
    T dot() const;

    /*!
     * @brief Returns the dot product of the vector with another vector
     */
    T dot( const Vector2<T>& other ) const;

    /*!
     * @brief Overload comparison operators
     */
    template <class T_> friend inline bool operator==( const Vector2<T_>& lhs, const Vector2<T_>& rhs );
    template <class T_> friend inline bool operator!=( const Vector2<T_>& lhs, const Vector2<T_>& rhs );
    template <class T_> friend inline bool operator< ( const Vector2<T_>& lhs, const Vector2<T_>& rhs );
    template <class T_> friend inline bool operator> ( const Vector2<T_>& lhs, const Vector2<T_>& rhs );
    template <class T_> friend inline bool operator<=( const Vector2<T_>& lhs, const Vector2<T_>& rhs );
    template <class T_> friend inline bool operator>=( const Vector2<T_>& lhs, const Vector2<T_>& rhs );

    /*!
     * @brief Overload arithmetic operators
     */
    Vector2<T>& operator++();
    Vector2<T>& operator--();
    Vector2<T> operator++( int );
    Vector2<T> operator--( int );
    Vector2<T>& operator+=( const Vector2<T>& rhs );
    Vector2<T>& operator-=( const Vector2<T>& rhs );

    // 2D coordinates
    T x;
    T y;
};

} // namespace GOL
