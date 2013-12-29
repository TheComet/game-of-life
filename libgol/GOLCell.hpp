// ----------------------------------------------------------------------------
// GOLCell.hpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <vector>

namespace GOL {

template <class COORD>
class Cell
{
public:

    /*!
     * @brief Default constructor
     */
    Cell( void );

    /*!
     * @brief Constructs a cell with the given coordinates
     */
    Cell( const COORD& coord );

    /*!
     * @brief Default destructor
     */
    ~Cell( void );

    /*!
     * @brief Bidirectionally links two cells together
     * This allows any cell to be connected to any other existing cell,
     * creating a complex representation of data.
     * @note If the linked ell is destroyed at any point in the future, it
     * automatically unlinks itself again without you having to worry.
     * @param other A pointer to another cell object to link to. Linking to
     * itself will silently fail. If the cell being linked is already linked,
     * this will silently fail.
     */
    void link( Cell* other );

    /*!
     * @brief Unlinks two cells that are linked
     * @note Trying to unlink a cells that wasn't linked in the first place
     * will silently fail
     * @param other A pointer to another cell to unlink
     */
    void unlink( Cell* other );

    /*!
     * @brief Unlinks all linked cells
     */
    void unlinkAll( void );

    /*!
     * @brief Returns the number of links the cell currently has
     * This can be useful for traversing the entire graph, as the value
     * returned can be used to jump from cell to cell.
     * @return The number of links the cell has
     */
    std::size_t getLinkCount( void ) const;

    /*!
     * @brief Returns a pointer to the linked cell
     * @param The linked cell to return. To get the total number of linked
     * cells, see @a getLinkCount
     * @return The pointer to the linked cell
     */
    Cell* getLinkedCell( std::size_t ID );

    /*!
     * @brief Sets the coordinates of the cell
     * @param coord The coordinates to give this cell
     */
    void setCoordinate( const COORD& coord );

    /*!
     * @brief Gets the coordinates of the cell
     * @return The coordinates of this cell
     */
    const COORD& getCoordinate() const;

private:

    std::vector<Cell*>  m_Links;
    COORD               m_Coordinate;
};

} // namespace GOL
