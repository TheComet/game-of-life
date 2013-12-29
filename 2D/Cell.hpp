// ----------------------------------------------------------------------------
// Cell.hpp
// ----------------------------------------------------------------------------

/*!
 * @brief A single cell in the field of life
 */
class Cell
{
public:

    /*!
     * @brief Default constructor
     */
    Cell();

    /*!
     * @brief Default destructor
     */
    ~Cell();

    /*!
     * @brief Kills the cell
     */
    void kill();

    /*!
     * @brief Revives the cell
     */
    void revive();

    /*!
     * @brief Returns the state of the cell (alive/dead)
     * @return Returns true if the cell is alive, false if otherwise
     */
    bool isAlive();

private:
    bool m_IsAlive;
};
