// ----------------------------------------------------------------------------
// GOLSortedList.hpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <iostream>

namespace GOL {

template <class T>
class SortedList
{
public:

    typedef T* iterator;
    typedef const T* const_iterator;

    /*!
     * @brief Default constructor
     */
    SortedList();

    /*!
     * @brief Constructs a sorted list with a specified pre-allocated chunk of memory
     * @brief preallocate The amount of memory in sizeof(T) to allocate
     */
    SortedList( std::size_t preallocate );

    /*!
     * @brief Copy constructor
     */
    SortedList( const SortedList<T>& that );

    /*!
     * @brief Default destructor
     */
    ~SortedList();

    /*!
     * @brief Inserts an item into the sorted list
     * Will perform a binary search of all existing items in the list to
     * determine where to insert
     * @brief item The item to insert
     */
    void insert( const T& item );

    /*!
     * @brief Erases an item from the list, shifting all data above it down
     * No memory re-allocation occurs during this process
     * @param pos The item to erase
     */
    void erase( std::size_t pos );

    /*!
     * @brief Erases an item from the list, shifting all data above it down
     * No memory re-allocation occurs during this process
     * @brief The item to erase
     */
    void erase( iterator it );

    /*!
     * @brief Searches the list for where the specified item would be inserted
     * Unlike @a find, this function will return the index of the item closest
     * to the value being searched for. If the item happens to exist, it will
     * be found, otherwise the next greater item is returned.
     * The complexity of the search is O(log(n)) (successive approximation).
     * @param item The item to search for
     * @return An index pointing to an insertion point in the list
     */
    std::size_t findInsertPosition( const T& item );

    /*!
     * @brief Searches the list for the specified item
     * The complexity of the search is O(log(n)) (successive approximation).
     * If the item wasn't found, an iterator pointing at @a end() is returned.
     * @param item The item to look for
     * @return An iterator pointing to the item if it exists
     */
    iterator find( const T& item );

    /*!
     * @brief Clears the content of the list without de-allocating any memory
     */
    void clear();

    /*!
     * @brief Resizes the list and forces re-allocation of memory
     */
    void resize( std::size_t size );

    /*!
     * @brief Returns a pointer to the beginning of the data in the list
     */
    iterator begin();

    /*!
     * @brief Returns a const pointer to the beginning of the data in the list
     */
    const_iterator begin() const;

    /*!
     * @brief Returns a pointer to the end of the data in the list
     */
    iterator end();

    /*!
     * @brief Returns a const pointer to the end of the data in the list
     */
    const_iterator end() const;

    /*!
     * @brief Returns the size of the list (how many items are currently inserted)
     */
    std::size_t size();

    /*!
     * @brief Returns the amount of memory the list has allocated
     */
    std::size_t allocatedSize();

    /*!
     * @brief Returns a reference to the specified item in the list
     * If the specified position in the list is out of bounds, an exception
     * is thrown.
     */
    T& at( std::size_t pos );

    /*!
     * @brief Returns a reference to the specified item in the list
     * If the specified position in the list is out of bounds, an exception
     * is thrown.
     */
    const T& at( std::size_t pos ) const;

    /*!
     * @brief Overload assignment operator
     */
    const SortedList<T>& operator=( const SortedList<T>& that );

    /*!
     * @brief Overload subscript operator
     * @note If _DEBUG is defined, this function calls @a at. If _DEBUG is not
     * defined, this function returns the data directly without bounds checking
     */
    T& operator[]( std::size_t pos );

    /*!
     * @brief Overload const subscript operator
     * @note If _DEBUG is defined, this function calls @a at. If _DEBUG is not
     * defined, this function returns the data directly without bounds checking
     */
    const T& operator[]( std::size_t pos ) const;

private:

    T*              m_Data;
    std::size_t     m_UsedSize;
    std::size_t     m_AllocatedSize;
};

} // namespace GOL
