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
    typename std::vector<T>::iterator it = std::lower_bound( m_CellList.begin(), m_CellList.end(), coordinate );
    if( it != m_CellList.end() )
        if( *it == coordinate )
            return;

    // add
    m_CellList.insert( it, coordinate );

    // process links
    // TODO test performance: link cells with each other
}

// ----------------------------------------------------------------------------
template <class T>
void GenericCellField<T>::removeCell( const T& coordinate )
{
    typename std::vector<T>::iterator it = std::lower_bound( m_CellList.begin(), m_CellList.end(), coordinate );
    if( it != m_CellList.end() )
        if( *it == coordinate )
            m_CellList.erase( it );
}

// ----------------------------------------------------------------------------
template <class T>
bool GenericCellField<T>::isCellAlive( const T& coordinate )
{
    typename std::vector<T>::iterator it = std::lower_bound( m_CellList.begin(), m_CellList.end(), coordinate );
    if( it != m_CellList.end() )
        if( *it == coordinate )
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
