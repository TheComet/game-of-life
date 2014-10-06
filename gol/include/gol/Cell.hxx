// ----------------------------------------------------------------------------
// GOLCell.cpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <GOLCell.hpp>
#include <Exception.hpp>

#include <sstream>

namespace GOL {

// ----------------------------------------------------------------------------
template <class COORD>
Cell<COORD>::Cell( void ) :
    m_Coordinate( COORD() )
{
}

// ----------------------------------------------------------------------------
template <class COORD>
Cell<COORD>::Cell( const COORD& coord ) :
    m_Coordinate( coord )
{
}

// ----------------------------------------------------------------------------
template <class COORD>
Cell<COORD>::~Cell( void )
{
    this->unlinkAll();
}

// ----------------------------------------------------------------------------
template <class COORD>
void Cell<COORD>::link( Cell* other )
{

    // self linkage
    if( this == other )
        return;

    // "this" already linked with other
    for( typename std::vector<Cell*>::iterator it = m_Links.begin(); it != m_Links.end(); ++it )
        if( *it == other )
            return;

    // safe to link both, as if "this" isn't linked with the other, the other is
    // guaranteed not be be linked with "this"
    this->m_Links.push_back( other );
    other->m_Links.push_back( this );
}

// ----------------------------------------------------------------------------
template <class COORD>
void Cell<COORD>::unlink( Cell* other )
{

    // unlink "this" from other
    for( typename std::vector<Cell*>::iterator it = this->m_Links.begin(); it != this->m_Links.end(); ++it )
        if( *it == other )
        {
            m_Links.erase( it );
            break;
        }

    // unlink other from "this"
    for( typename std::vector<Cell*>::iterator it = other->m_Links.begin(); it != other->m_Links.end(); ++it )
        if( *it == this )
        {
            other->m_Links.erase( it );
            break;
        }
}

// ----------------------------------------------------------------------------
template <class COORD>
void Cell<COORD>::unlinkAll( void )
{
    typename std::vector<Cell*>::iterator it = this->m_Links.begin();
    while( it != this->m_Links.end() )
    {

        // unlink other from this
        for( typename std::vector<Cell*>::iterator it2 = (*it)->m_Links.begin(); it2 != (*it)->m_Links.end(); ++it2 )
            if( *it2 == this )
            {
                (*it)->m_Links.erase( it2 );
                break;
            }

        // unlink this from other
        it = this->m_Links.erase( it );
    }
}

// ----------------------------------------------------------------------------
template <class COORD>
std::size_t Cell<COORD>::getLinkCount( void ) const
{
    return m_Links.size();
}

// ----------------------------------------------------------------------------
template <class COORD>
Cell<COORD>* Cell<COORD>::getLinkedCell( std::size_t ID )
{
    return m_Links.at(ID);
}

// ----------------------------------------------------------------------------
template <class COORD>
void Cell<COORD>::setCoordinate( const COORD& coord )
{
    m_Coordinate = coord;
}

// ----------------------------------------------------------------------------
template <class COORD>
const COORD& Cell<COORD>::getCoordinate() const
{
    return m_Coordinate;
}

} // namespace GOL
