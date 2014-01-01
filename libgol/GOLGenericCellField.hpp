// ----------------------------------------------------------------------------
// GOLGenericCellField.hpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <GOLSortedList.hxx>

namespace GOL {

template <class T>
class GenericCellField
{
public:

    /*!
     * @brief Default constructor
     */
    GenericCellField();

    /*!
     * @brief Default destructor
     */
    ~GenericCellField();

    void addCell( const T& coordinate );
    void removeCell( const T& coordinate );
    bool isCellAlive( const T& coordinate );

    void calculateNextGeneration();
    void calculatePreviousGeneration();

private:

    SortedList<T> m_CellList;
};

} // namespace GOL
