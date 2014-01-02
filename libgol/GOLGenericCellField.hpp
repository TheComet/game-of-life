// ----------------------------------------------------------------------------
// GOLGenericCellField.hpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <GOLSortedList.hxx>
#include <GOLRule.hpp>

namespace GOL {

template <class T>
class GenericCellField
{
public:

    /*!
     * @brief Default constructor
     * Constructs a cell field using the default rules of Conway:
     * - Any live cell with fewer than two live neighbours dies, as if caused by under-population.
     * - Any live cell with two or three live neighbours lives on to the next generation.
     * - Any live cell with more than three live neighbours dies, as if by overcrowding.
     * - Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
     */
    GenericCellField();

    /*!
     * @brief Constructs a cell field using user defined rules
     * @param rule The rules to use. See @a Rule for more information
     */
    GenericCellField( const Rule& rule );

    /*!
     * @brief Default destructor
     */
    virtual ~GenericCellField();

    /*!
     * @brief Adds a cell at the specified coordinates
     * If the cell already exists, nothing will happen
     * @param coordinate The coordinate at which to add the cell
     */
    void addCell( const T& coordinate );

    /*!
     * @brief Removes a cell from the specified coordinates
     * If the cell doesn't exist, nothing will happen
     * @param coordinate The coordinate from which to remove the cell
     */
    void removeCell( const T& coordinate );

    /*!
     * @brief Checks whether the specified cell is alive or dead
     * @param coordinate The coordinate of the cell to check
     * @return Returns true if the specified cell is alive, false if otherwise
     */
    bool isCellAlive( const T& coordinate );

    /*!
     * @brief Sets new rules for this cell field
     * @param rule The new rule to use. See @a Rule for more information
     */
    void setRule( const Rule& rule );

    /*!
     * @brief Returns the rules currently in place
     * @return The rules being used. See @a Rule for more information
     */
    const Rule& getRule() const;

    /*!
     * @brief Calculates the next generation of cells using the rules specified
     */
    virtual void calculateNextGeneration() = 0;

    /*!
     * @brief Calculates the previous generation of cells using the rules specified
     */
    virtual void calculatePreviousGeneration() = 0;

protected:

    Rule            m_Rule;
    SortedList<T>   m_CellList;
};

} // namespace GOL
