// ----------------------------------------------------------------------------
// GOLGenericCellField.hxx
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <GOLGenericCellField.hpp>

namespace GOL {

// ----------------------------------------------------------------------------
template <class T>
GenericCellField<T>::GenericCellField() :
    m_Rule( Rule(2,3,3,3) ) // default Conway's rules
{
}

// ----------------------------------------------------------------------------
template <class T>
GenericCellField<T>::GenericCellField( const Rule& rule ) :
    m_Rule( rule )
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
void GenericCellField<T>::setRule( const Rule& rule )
{
    m_Rule = rule;
}

// ----------------------------------------------------------------------------
template <class T>
const Rule& GenericCellField<T>::getRule() const
{
    return m_Rule;
}

} // namespace GOL
