// ----------------------------------------------------------------------------
// GOLGenericCellField.hxx
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <gol/GenericCellField.hpp>

namespace GOL {

// ----------------------------------------------------------------------------
template <class T>
GenericCellField<T>::GenericCellField()
{
    // canot be called because it's private
}

// ----------------------------------------------------------------------------
template <class T>
GenericCellField<T>::GenericCellField( const Rule& rule ) :
    m_Rule( rule ),
    m_ActiveCellList(0)
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

    // std::set won't insert if the element already exists
    m_CellList[m_ActiveCellList].insert( coordinate );

    // process links
    // TODO test performance: link cells with each other
}

// ----------------------------------------------------------------------------
template <class T>
void GenericCellField<T>::removeCell( const T& coordinate )
{
    typename std::set<T>::iterator it = m_CellList[m_ActiveCellList].find( coordinate );
    if( it != m_CellList[m_ActiveCellList].end() )
        m_CellList[m_ActiveCellList].erase( it );
}

// ----------------------------------------------------------------------------
template <class T>
bool GenericCellField<T>::isCellAlive( const T& coordinate )
{
    if( m_CellList[m_ActiveCellList].find( coordinate ) != m_CellList[m_ActiveCellList].end() )
        return true;
    return false;
}

// ----------------------------------------------------------------------------
template <class T>
const std::set<T>& GenericCellField<T>::getActiveCellList() const
{
    return m_CellList[ m_ActiveCellList ];
}

// ----------------------------------------------------------------------------
template <class T>
std::vector<T>& GenericCellField<T>::getAdjacentCellLookupTable()
{
    return m_AdjacentCellLookupTable;
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

// ----------------------------------------------------------------------------
template <class T>
void GenericCellField<T>::calculateNextGeneration()
{

    // prepare target list and post process list
    std::size_t targetCellList = 1 - m_ActiveCellList;
    m_CellList[targetCellList].clear();
    m_PostProcessCellList.clear();

    // iterate over all active cells in active list
    for( typename std::set<T>::iterator it = m_CellList[m_ActiveCellList].begin();
         it != m_CellList[m_ActiveCellList].end();
         ++it )
    {

        // iterate over adjacent cells of currently selected cell
        unsigned int neighbours = 0;
        for( typename std::vector<T>::iterator adj_it = m_AdjacentCellLookupTable.begin();
             adj_it != m_AdjacentCellLookupTable.end();
             ++adj_it )
        {
            T adjacentCoordinate = *it + *adj_it;

            // adjacent cell is alive
            // count
            if( m_CellList[m_ActiveCellList].find(adjacentCoordinate) != m_CellList[m_ActiveCellList].end() )
                ++neighbours;

            // adjacent cell is dead
            // add to potential revival list
            else
                m_PostProcessCellList.insert( adjacentCoordinate );
        }

        // apply rules for underpopulation and overpopulation to determine if
        // this cell can live. If so, add to target list
        if( neighbours >= m_Rule.getUnderpopulationThreshold() &&
            neighbours <= m_Rule.getOverpopulationThreshold() )
            m_CellList[targetCellList].insert( *it );
    }

    // iterate over all dead cells in revival list
    for( typename std::set<T>::iterator it = m_PostProcessCellList.begin();
         it != m_PostProcessCellList.end();
         ++it )
    {

        // iterate over adjacent cells of currently selected cell and count alive neighbours
        unsigned int neighbours = 0;
        for( typename std::vector<T>::iterator adj_it = m_AdjacentCellLookupTable.begin();
             adj_it != m_AdjacentCellLookupTable.end();
             ++adj_it )
            if( m_CellList[m_ActiveCellList].find(*it + *adj_it) != m_CellList[m_ActiveCellList].end() )
                ++neighbours;

        // apply reproduction rules to determine if this sell can be resurected.
        // if so, add to target list
        if( neighbours >= m_Rule.getLowerReproductionThreshold() &&
            neighbours <= m_Rule.getUpperReproductionThreshold() )
            m_CellList[targetCellList].insert( *it );
    }

    // swap active lists
    m_ActiveCellList = targetCellList;
}

// ----------------------------------------------------------------------------
template <class T>
void GenericCellField<T>::calculatePreviousGeneration()
{

}

// ----------------------------------------------------------------------------
template <class T>
void GenericCellField<T>::reset()
{
    m_CellList[0].clear();
    m_CellList[1].clear();
    m_ActiveCellList = 0;
}

} // namespace GOL
