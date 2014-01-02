// ----------------------------------------------------------------------------
// GOLCellField2D.hpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <GOLGenericCellField.hxx>
#include <GOLVector2.hxx>

namespace GOL {

class CellField2D :
    public GenericCellField< Vector2<int> >
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
    CellField2D();

    /*!
     * @brief Constructs a 2D cell field with the specified rules
     */
    CellField2D( const Rule& rule );

    /*!
     * @brief Default destructor
     */
    ~CellField2D();

};

} // namespace GOL
