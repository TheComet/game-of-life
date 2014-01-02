// ----------------------------------------------------------------------------
// GOLSortedList.hxx
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <GOLSortedList.hpp>

#include <Exception.hpp>
#include <sstream>

namespace GOL {

// ----------------------------------------------------------------------------
template <class T>
SortedList<T>::SortedList() :
    m_Data(0),
    m_UsedSize(0),
    m_AllocatedSize(0)
{
}

// ----------------------------------------------------------------------------
template <class T>
SortedList<T>::SortedList( std::size_t preallocate ) :
    m_Data(0),
    m_UsedSize(preallocate),
    m_AllocatedSize(preallocate)
{
    m_Data = new T[preallocate];
    for( std::size_t n = 0; n != preallocate; ++n )
        m_Data[n] = T();
}

// ----------------------------------------------------------------------------
template <class T>
SortedList<T>::SortedList( const SortedList<T>& that ) :
    m_Data(0),
    m_UsedSize(0),
    m_AllocatedSize(0)
{
    *this = that;
}

// ----------------------------------------------------------------------------
template <class T>
SortedList<T>::~SortedList()
{
    if( m_Data )
        delete[] m_Data;
}

// ----------------------------------------------------------------------------
template <class T>
void SortedList<T>::insert( const T& item )
{

    if( item.x == -1 && item.y == -1 )
        int a = 5;

    // get insert position
    std::size_t insertPos = this->findInsertPosition( item );

    if( insertPos > m_UsedSize )
        int a = 5;

    // re-allocate if necessary
    if( m_UsedSize == m_AllocatedSize )
    {
        ++m_AllocatedSize;
        ++m_UsedSize;
        T* temp = new T[m_UsedSize];
        for( std::size_t n = 0; n != insertPos; ++n )
            temp[n] = m_Data[n];
        for( std::size_t n = insertPos; n != m_UsedSize-1; ++n )
            temp[n+1] = m_Data[n];
        if( m_Data )
            delete[] m_Data;
        m_Data = temp;
        m_Data[insertPos] = item;

    // insert item without re-allocating
    }else
    {
        for( std::size_t n = insertPos; n < m_UsedSize; ++n )
            m_Data[n+1] = m_Data[n];
        m_Data[insertPos] = item;
        ++m_UsedSize;
    }
}

// ----------------------------------------------------------------------------
template <class T>
void SortedList<T>::erase( std::size_t pos )
{
    if( pos >= m_UsedSize )
    {
        std::stringstream ss; ss << "[SortedList::erase] Error: Index out of bounds: " << pos << ", actual list size: " << m_UsedSize;
        throw Exception( ss.str() );
    }

    // shift top part of list down, overwriting value to erase
    for( std::size_t n = pos+1; n != m_UsedSize; ++n )
        m_Data[n-1] = m_Data[n];
    --m_UsedSize;
}

// ----------------------------------------------------------------------------
template <class T>
void SortedList<T>::erase( SortedList<T>::iterator it )
{
    // shift top part of list down, overwriting value to erase
    for( iterator n = it+1; n != this->end(); ++n )
        *(n-1) = *n;
    --m_UsedSize;
}

// ----------------------------------------------------------------------------
template <class T>
std::size_t SortedList<T>::findInsertPosition( const T& item )
{

    // no data
    if( !m_Data )
        return 0;

    // binary search
    std::size_t foundPos = m_UsedSize >> 1;
    std::size_t step = foundPos;
    do
    {
        step >>= 1;
        if( m_Data[foundPos] < item )
            foundPos += step;
        else
            foundPos -= step;
    } while( step > 1 );
    // requires one more step
    if( foundPos != 0 )
        if( m_Data[foundPos] > item )
            --foundPos;
    if( foundPos < m_UsedSize )
        if( m_Data[foundPos] < item )
            ++foundPos;
    return foundPos;
}

// ----------------------------------------------------------------------------
template <class T>
typename SortedList<T>::iterator SortedList<T>::find( const T& item )
{
    std::size_t foundPos = this->findInsertPosition( item );
    if( foundPos == m_UsedSize )
        return m_Data+m_UsedSize;
    if( m_Data[foundPos] != item )
        foundPos = m_UsedSize;
    return m_Data+foundPos;
}

// ----------------------------------------------------------------------------
template <class T>
void SortedList<T>::clear()
{
    m_UsedSize = 0;
}

// ----------------------------------------------------------------------------
template <class T>
void SortedList<T>::resize( std::size_t size )
{
    T* temp = new T[size];
    if( m_UsedSize > size )
        m_UsedSize = size;
    for( std::size_t n = 0; n != m_UsedSize; ++n )
        temp[n] = m_Data[n];
    for( std::size_t n = m_UsedSize; n < size; ++n )
        temp[n] = T();
    delete[] m_Data;
    m_Data = temp;
    m_AllocatedSize = size;
    m_UsedSize = size;
}

// ----------------------------------------------------------------------------
template <class T>
typename SortedList<T>::iterator SortedList<T>::begin()
{
    return m_Data;
}

// ----------------------------------------------------------------------------
template <class T>
typename SortedList<T>::const_iterator SortedList<T>::begin() const
{
    return m_Data;
}

// ----------------------------------------------------------------------------
template <class T>
typename SortedList<T>::iterator SortedList<T>::end()
{
    return (m_Data+m_UsedSize);
}

// ----------------------------------------------------------------------------
template <class T>
typename SortedList<T>::const_iterator SortedList<T>::end() const
{
    return (m_Data+m_UsedSize);
}

// ----------------------------------------------------------------------------
template <class T>
std::size_t SortedList<T>::size()
{
    return m_UsedSize;
}

// ----------------------------------------------------------------------------
template <class T>
std::size_t SortedList<T>::allocatedSize()
{
    return m_AllocatedSize;
}

// ----------------------------------------------------------------------------
template <class T>
T& SortedList<T>::at( std::size_t index )
{
    if( index >= m_UsedSize )
    {
        std::stringstream ss; ss << "[SortedList::operator[]] Error: Index out of bounds: " << index << ", actual list size: " << m_UsedSize;
        throw Exception( ss.str() );
    }
    return m_Data[index];
}

// ----------------------------------------------------------------------------
template <class T>
const T& SortedList<T>::at( std::size_t index ) const
{
    if( index >= m_UsedSize )
    {
        std::stringstream ss; ss << "[SortedList::operator[]] Error: Index out of bounds: " << index << ", actual list size: " << m_UsedSize;
        throw Exception( ss.str() );
    }
    return m_Data[index];
}

// ----------------------------------------------------------------------------
template <class T>
const SortedList<T>& SortedList<T>::operator=( const SortedList<T>& that )
{
    if( this == &that )
        return *this;

    // don't re-allocate if size of "this" is equal or greater than "that"
    // just copy data across
    if( m_AllocatedSize >= that.m_AllocatedSize )
    {
        for( std::size_t n = 0; n != that.m_UsedSize; ++n )
            m_Data[n] = that.m_Data[n];

    // re-allocate and copy data across
    }else
    {
        T* temp = new T[that.m_UsedSize];
        for( std::size_t n = 0; n != that.m_UsedSize; ++n )
            temp[n] = that.m_Data[n];
        delete[] m_Data;
        m_Data = temp;
        m_AllocatedSize = that.m_UsedSize;
    }
    m_UsedSize = that.m_UsedSize;
}

// ----------------------------------------------------------------------------
template <class T>
T& SortedList<T>::operator[]( std::size_t index )
{
#ifdef _DEBUG
    return this->at(index);
#else
    return m_Data[index];
#endif
}

// ----------------------------------------------------------------------------
template <class T>
const T& SortedList<T>::operator[]( std::size_t index ) const
{
#ifdef _DEBUG
    return this->at(index);
#else
    return m_Data[index];
#endif
}

} // namespace GOL
