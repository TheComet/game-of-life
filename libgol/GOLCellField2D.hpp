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
     * @note Please read @a GenericCellField for more information on what rules
     * are set by default
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

    /*!
     * @brief
     */

};

} // namespace GOL
