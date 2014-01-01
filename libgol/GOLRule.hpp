// ----------------------------------------------------------------------------
// GOLRule.hpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

namespace GOL {

class Rule
{
public:

    /*!
     * @brief Constructs a @a Rule object with the rules specified
     * @param underpopulationThreshold Sets the lower threshold of the minimum
     * required cells to surround an existing cell to keep it alive. The most
     * common value used here is 2.
     * @param overpopulationThreshold Sets the upper threshold of the maximum
     * allowed cells to surround an existing cell without it dying. The most
     * common value used here is 3.
     * @param lowerReproductionThreshold Sets the lower threshold for the
     * minimum required cells to surround a dead cell in order to bring it back
     * to life. The most common value used here is 3.
     * @param upperReproductionThreshold Sets the upper threshold for the
     * maximum required cells to surround a dead cell in order to bring it back
     * to life. The most commong value used here is 3.
     * @exception If underpopulationThreshold>overpopulationThreshold or
     * lowerReproductionThreshold>upperReproductionThreshold, an exception is
     * thrown.
     */
    Rule( unsigned int underpopulationThreshold,
          unsigned int overpopulationThreshold,
          unsigned int lowerReproductionThreshold,
          unsigned int upperReproductionThreshold );

    /*!
     * @brief Default destructor
     */
    ~Rule();

    /*!
     * @brief Gets the underpopulation threshold
     */
    inline unsigned int getUnderpopulationThreshold()
    { return m_UnderpopulationThreshold; }

    /*!
     * @brief Gets the overpopluation threshold
     */
    inline unsigned int getOverpopulationThreshold()
    { return m_OverpopulationThreshold; }

    /*!
     * @brief Gets the lower reproduction threshold
     */
    inline unsigned int getLowerReproductionThreshold()
    { return m_LowerReproductionThreshold; }

    /*!
     * @brief Gets the upper reproduction threshold
     */
    inline unsigned int getUpperReproductionThreshold()
    { return m_UpperReproductionThreshold; }

private:

    /*!
     * @brief Default constructor
     * Set to private - Rules must be provided by user
     */
    Rule();

    unsigned int m_UnderpopulationThreshold;
    unsigned int m_OverpopulationThreshold;
    unsigned int m_LowerReproductionThreshold;
    unsigned int m_UpperReproductionThreshold;
};

} // namespace GOL
