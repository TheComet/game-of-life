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
     * @brief Normalises the vector
     */
    void normalise();

    /*!
     * @brief Returns a new normalised version of the object without affecting the original
     */
    Vector3 getNormalised() const;

    /*!
     * @brief Returns the dot product of the vector with itself
     */
    const T dot() const;

    /*!
     * @brief Returns the dot product of the vector with another vector
     */
    const T dot( const Vector3<T>& other ) const;

    /*!
     * @brief Calculates the cross product with another vector
     * The result of this computation is stored in the original object, i.e. it
     * modifies itself with the result
     */
    void cross( const Vector3<T>& other );

    /*!
     * @brief Returns the cross product with another vector without affecting the original object
     * The result of this computation is returned and does not change the state of the object
     */
    Vector3<T> getCross( const Vector3<T>& other ) const;

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

    /*!
     * @brief Overload arithmetic operators
     */
    Vector3<T>& operator++();
    Vector3<T>& operator--();
    Vector3<T> operator++( int );
    Vector3<T> operator--( int );
    Vector3<T>& operator+=( const Vector3<T>& rhs );
    Vector3<T>& operator-=( const Vector3<T>& rhs );

    // 3D coordinates
    T x;
    T y;
    T z;
};

} // namespace GOL
