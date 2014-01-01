// ----------------------------------------------------------------------------
// GOLGenericCellField.hxx
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <GOLGenericCellField.hpp>

#include <algorithm>

namespace GOL {

// ----------------------------------------------------------------------------
template <class T>
GenericCellField<T>::GenericCellField()
{
}

// ----------------------------------------------------------------------------
template <class T>
GenericCellField<T>::~GenericCellField()
{
}

// ----------------------------------------------------------------------------
template <class T>
void GenericCellField<T>::addCell( const T& coordinate )
{

    // make sure cell at specified coordinates doesn't exist yet
    typename SortedList<T>::iterator it = m_CellList.find( coordinate );
    if( it != m_CellList.end() )
        return;

    // add
    m_CellList.insert( coordinate );

    // process links
    // TODO test performance: link cells with each other
}

// ----------------------------------------------------------------------------
template <class T>
void GenericCellField<T>::removeCell( const T& coordinate )
{
    typename SortedList<T>::iterator it = m_CellList.find( coordinate );
    if( it != m_CellList.end() )
        m_CellList.erase( it );
}

// ----------------------------------------------------------------------------
template <class T>
bool GenericCellField<T>::isCellAlive( const T& coordinate )
{
    if( m_CellList.find( coordinate ) != m_CellList.end() )
        return true;
    return false;
}

// ----------------------------------------------------------------------------
template <class T>
void GenericCellField<T>::calculateNextGeneration()
{

}

// ----------------------------------------------------------------------------
template <class T>
void GenericCellField<T>::calculatePreviousGeneration()
{

}

} // namespace GOL
