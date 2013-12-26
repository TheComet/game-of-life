// --------------------------------------------------------------
// SignedArray2D.hpp
// --------------------------------------------------------------

// --------------------------------------------------------------
// include files

#include <iostream>
#include <vector>

/*!
 * @brief Wraps a dynamic 2-dimensional array with std::vector< std::vector<T> > at its core
 */
template <class T>
class SignedArray2D
{
public:

    /*!
     * @brief Default constructor
     */
    SignedArray2D( void );

    /*!
     * @brief Constructor setting the default content of the array
     * see @a setDefaultContent for more information
     * @param content The content to use
     */
    SignedArray2D( const T& content );

    /*!
     * @brief Copy Constructor
     * @param cp The other 2D array to copy
     */
    SignedArray2D( const SignedArray2D& that );

    /*!
     * @brief Copy Constructor with setting the default content of the array
     */
    SignedArray2D( const SignedArray2D& that, const T& content );

    /*!
     * @brief Default destructor
     */
    ~SignedArray2D( void );

    /*!
     * @brief Sets the default initial content of the array
     * Sets what content should be inserted into the array
     * when first allocated or cleared.
     * @param content The content to use
     */
    void setDefaultContent( const T& content );

    /*!
     * @brief Retrieves the default content of the array
     */
    const T& getDefaultContent( void ) const;

    /*!
     * @brief Resizes the SignedArray2D to the specified dimensions
     * The new size of the array is defined by a rectangle specified by two
     * 2D coordinates x1,y1 and x2,y2, where the new size of the array is
     * specified to be (x2-x1,y2-y1).
     * Because it's a signed array, it can be resized with negative boundaries,
     * so long as x1 is never greater than x2 and y1 is never greater than y2.
     * @param x1 The x-coordinate of the lower corner of the rectangle
     * @param y1 The y-coordinate of the lower corner of the rectangle
     * @param x2 The x-coordinate of the higher corner of the rectangle
     * @param y2 The y-coordinate of the higher corner of the rectangle
     * @exception An exception is thrown if
     */
    void resize( int x1, int y1, int x2, int y2 );

    /*!
     * @brief Mirrors the array along its X axis
     */
    void mirrorX( void );

    /*!
     * @brief Mirrors the array along its Y axis
     */
    void mirrorY( void );

    /*!
     * @brief Gets the size of the array in the x dimension
     * @return std::size_t of the array's x dimension
     */
    std::size_t sizeX( void ) const;

    /*!
     * @brief Gets the size of the array in the y dimension
     * @return std::size_t of the array's y dimension
     */
    std::size_t sizeY( void ) const;

    /*!
     * @brief Gets a character from the array at the specified coordinates
     * Enables the use of reading from the SignedArray2D with boundary checking
     * @exception Throws a Chocobun::Exception if the coordinates are
     * out of bounds
     * @return The data stored at the specified coordinates
     */
    const T& at( int x, int y ) const;

    /*!
     * @brief Gets a character from the array at the specified coordinates
     * Enables the use of writing to the array with boundary checking
     * @exception Throws a Chocobun::Exception if the coordinates are
     * out of bounds
     * @return The data stored at the specified coordinates
     */
    T& at( int x, int y );

    /*!
     * @brief Overload assignment operator for array to array assignments
     */
    SignedArray2D<T>& operator=( const SignedArray2D<T>& that );

private:

    T                               m_DefaultContent;
    std::size_t                     m_SizeX;
    std::size_t                     m_SizeY;
    int                             m_OffsetX;
    int                             m_OffsetY;
    std::vector< std::vector<T> >   m_Array; // NOTE: outer vector: x-dimension, inner vector: y-dimension
};
