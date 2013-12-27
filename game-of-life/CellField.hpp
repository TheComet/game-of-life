// ----------------------------------------------------------------------------
// CellField.hpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <iostream>

#include <Drawable.hpp>
#include <Cell.hpp>
#include <SignedArray2D.hxx>

/*!
 * @brief Simulates the game of life
 */
class CellField :
    public Drawable
{
public:

    /*!
     * @brief Default constructor
     */
    CellField();

    /*!
     * @brief Default destructor
     */
    ~CellField();

    /*!
     * @brief Calculates the next frame according to Conway's rules
     */
    void calculateNextFrame();

    /*!
     * @brief Calculates the previous frame according to Conway's rules
     */
    void calculatePreviousFrame();

    /*!
     * @brief Returns the total size of the cell field as an unsigned 2D vector
     * @note The size of the field will grow over time
     * @return The size of the field
     */
    sf::Vector2u getSize();

    /*!
     * @brief Returns the X size of the cell field
     * @note The size of the field will grow over time
     * @return The X size of the field
     */
    std::size_t getSizeX();

    /*!
     * @brief Returns the Y size of the cell field
     * @note The size of the field will grow over time
     * @return The Y size of the field
     */
    std::size_t getSizeY();

    /*!
     * @brief
     */
    void draw( sf::RenderTarget* target, sf::Vector2f viewSize, sf::Vector2f viewPosition, float zoomFactor );

private:
    SignedArray2D<Cell> m_Cells;
};
