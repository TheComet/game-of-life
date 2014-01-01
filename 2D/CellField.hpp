// ----------------------------------------------------------------------------
// CellField.hpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <iostream>

#include <Drawable.hpp>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

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
     * @brief Toggles a cell at the specified coordinates
     * If the cell is out of bounds of the internal array, and the cell is
     * being brought to life, said array is simply expanded so it fits.
     * Note that the array might also shrink if cells are removed.
     * @param x The x-coordinate of the cell to toggle
     * @param y The y-coordinate of the cell to toggle
     */
    void toggleCell( int x, int y );

    /*!
     * @brief Returns the state of a cell at the specified coordinates
     * If the coordinates of the cell are out of bounds of the internal array,
     * "false" is returned.
     * @param x The x-coordinate of the cell
     * @param y The y-coordinate of the cell
     * @return True if the cell is alive, false if otherwise
     */
    bool isCellAlive( int x, int y );

    /*!
     * @brief Calculates the next frame according to Conway's rules
     */
    void calculateNextFrame();

    /*!
     * @brief Calculates the previous frame according to Conway's rules
     */
    void calculatePreviousFrame();

    /*!
     * @brief Forces generation of an internal list of active cells
     * This is used to optimise the calculation of the next or previous
     * generation, but should only be called after cells have been manipulated
     * externally
     */
    void regenerateActiveCellList();

    /*!
     * @brief Resets the field and frees all memory
     */
    void reset();

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

    /*!
     * @brief Determines the optimal size of the array and resizes it to that
     * By default, the optimum resize is only calculated if cells are pushing
     * on the boundaries of the array. Optionally, it's possible to force the
     * algorithm to calculate the optimum resize.
     * @param forceResize Forces the calculation of an optimum resize.
     */
    void optimumArrayResize( bool forceResize = false );

private:

    /*!
     * @brief Expands the array by a fixed number on every side
     * The coordinates passed to this function are guaranteed to fit in the
     * newly resized array
     * @param x The x-coordinate that must fit into the new array
     * @param y The y-coordinate that must fit into the new array
     */
    void expandArray( int x, int y );

    SignedArray2D<Cell> m_CellBuffer[2];
    std::vector<sf::Vector2i> m_ActiveCellList[2];

    sf::Texture m_CellTexture;
    sf::Sprite m_CellSprite;

    int m_BoundaryX1;
    int m_BoundaryY1;
    int m_BoundaryX2;
    int m_BoundaryY2;
};
