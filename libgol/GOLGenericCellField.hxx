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
    m_ActiveCellList(0)
{
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

    // make sure cell at specified coordinates doesn't exist yet
    typename SortedList<T>::iterator it = m_CellList[m_ActiveCellList].find( coordinate );
    if( it != m_CellList[m_ActiveCellList].end() )
        return;

    // add
    m_CellList[m_ActiveCellList].insert( coordinate );

    // process links
    // TODO test performance: link cells with each other
}

// ----------------------------------------------------------------------------
template <class T>
void GenericCellField<T>::removeCell( const T& coordinate )
{
    typename SortedList<T>::iterator it = m_CellList[m_ActiveCellList].find( coordinate );
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

    std::cout << "alive cell lookup table" << std::endl;
    for( typename std::vector<T>::iterator it = m_AdjacentCellLookupTable.begin();
         it != m_AdjacentCellLookupTable.end();
         ++it )
    {
        std::cout << it->x << "," << it->y << std::endl;
    }

    std::cout << "current frame" << std::endl;
    for( typename SortedList<T>::iterator it = m_CellList[m_ActiveCellList].begin();
         it != m_CellList[m_ActiveCellList].end();
         ++it )
    {
        std::cout << it->x << "," << it->y << std::endl;
    }

    // prepare target list
    std::size_t targetCellList = 1 - m_ActiveCellList;
    m_CellList[targetCellList].clear();

    // prepare revival list
    // number of surrounding dead cells should approximately be alive*adjacentCount*0.8
    // pre-allocate that amount of memory to decrease re-allocations
    SortedList<T> revivalList;
    revivalList.resize( m_CellList[m_ActiveCellList].size()*m_AdjacentCellLookupTable.size()*0.8 );
    revivalList.clear();

    // iterate over all active cells in active list
    for( typename SortedList<T>::iterator it = m_CellList[m_ActiveCellList].begin();
         it != m_CellList[m_ActiveCellList].end();
         ++it )
    {

        std::cout << "processing living: " << it->x << "," << it->y << std::endl;

        // iterate over adjacent cells of currently selected cell
        unsigned int neighbours = 0;
        for( typename std::vector<T>::iterator adj_it = m_AdjacentCellLookupTable.begin();
             adj_it != m_AdjacentCellLookupTable.end();
             ++adj_it )
        {
            T adjacentCoordinate = *it + *adj_it;
            std::cout << "    testing neighbour: " << adjacentCoordinate.x << "," << adjacentCoordinate.y << ", result: ";

            // adjacent cell is alive
            // count
            if( m_CellList[m_ActiveCellList].find(adjacentCoordinate) != m_CellList[m_ActiveCellList].end() )
            {
                std::cout << "yes" << std::endl;
                ++neighbours;


            // adjacent cell is dead
            // add to potential revival list
            }else{
                revivalList.insert( adjacentCoordinate );
                std::cout << "no" << std::endl;
            }
        }

        std::cout << "    total neighbours: " << neighbours << std::endl;

        // apply rules for underpopulation and overpopulation to determine if
        // this cell can live. If so, add to target list
        if( neighbours >= m_Rule.getUnderpopulationThreshold() &&
            neighbours <= m_Rule.getOverpopulationThreshold() )
            m_CellList[targetCellList].insert( *it );
    }

    std::cout << "target cell list after processing living" << std::endl;
    for( typename SortedList<T>::iterator it = m_CellList[targetCellList].begin();
         it != m_CellList[targetCellList].end();
         ++it )
    {
        std::cout << it->x << "," << it->y << std::endl;
    }

    std::cout << "revival list" << std::endl;
    for( typename SortedList<T>::iterator it = revivalList.begin();
         it != revivalList.end();
         ++it )
    {
        std::cout << it->x << "," << it->y << std::endl;
    }

    // iterate over all dead cells in revival list
    for( typename SortedList<T>::iterator it = revivalList.begin();
         it != revivalList.end();
         ++it )
    {

        // iterate over adjacent cells of currently selected cell and count alive neighbours
        unsigned int neighbours = 0;
        for( typename std::vector<T>::iterator adj_it = m_AdjacentCellLookupTable.begin();
             adj_it != m_AdjacentCellLookupTable.end();
             ++adj_it )
        {
            if( m_CellList[m_ActiveCellList].find(*it + *adj_it) != m_CellList[m_ActiveCellList].end() )
                ++neighbours;
        }

        // apply reproduction rules to determine if this sell can be resurected.
        // if so, add to target list
        if( neighbours >= m_Rule.getLowerReproductionThreshold() &&
            neighbours <= m_Rule.getUpperReproductionThreshold() )
            m_CellList[targetCellList].insert( *it );
    }

    // swap active lists
    m_ActiveCellList = targetCellList;

    std::cout << "target list frame after processing" << std::endl;
    for( typename SortedList<T>::iterator it = m_CellList[m_ActiveCellList].begin();
         it != m_CellList[m_ActiveCellList].end();
         ++it )
    {
        std::cout << it->x << "," << it->y << std::endl;
    }

}

// ----------------------------------------------------------------------------
template <class T>
void GenericCellField<T>::calculatePreviousGeneration()
{

}

} // namespace GOL
