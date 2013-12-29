// ----------------------------------------------------------------------------
// GOLGenericCellField.hpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

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

private:

};

} // namespace GOL
