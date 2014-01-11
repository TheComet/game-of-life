// ----------------------------------------------------------------------------
// GOLGenericCellField.hpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <GOLSortedList.hxx>
#include <GOLRule.hpp>

#include <vector>

namespace GOL {

template <class T>
class GenericCellField
{
public:

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

    SortedList<T>& getActiveCellList() { return m_CellList[m_ActiveCellList]; }

    /*!
     * @brief Returns a reference to the lookup table of adjacent cells
     * The lookup table needs to be filled before generations can be computed.
     */
    std::vector<T>& getAdjacentCellLookupTable();

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
    void calculateNextGeneration();

    /*!
     * @brief Calculates the previous generation of cells using the rules specified
     */
    void calculatePreviousGeneration();

protected:

    Rule            m_Rule;
    SortedList<T>   m_CellList[2];
    std::vector<T>  m_AdjacentCellLookupTable;
    std::size_t     m_ActiveCellList;

private:

    /*!
     * @brief Default constructor
     * Prevent construction without rules
     */
    GenericCellField();
};

} // namespace GOL
