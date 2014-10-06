// ----------------------------------------------------------------------------
// GOLRule.cpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <gol/Rule.hpp>
#include <gol/Exception.hpp>
#include <sstream>

namespace GOL {

// ----------------------------------------------------------------------------
Rule::Rule()
{
}

// ----------------------------------------------------------------------------
Rule::Rule( unsigned int underpopulationThreshold,
            unsigned int overpopulationThreshold,
            unsigned int lowerReproductionThreshold,
            unsigned int upperReproductionThreshold ) :
    m_UnderpopulationThreshold( underpopulationThreshold ),
    m_OverpopulationThreshold( overpopulationThreshold ),
    m_LowerReproductionThreshold( lowerReproductionThreshold ),
    m_UpperReproductionThreshold( upperReproductionThreshold )
{
    if( underpopulationThreshold>overpopulationThreshold )
    {
        std::stringstream ss; ss << "[Rule::Rule] Error: Underpopulation threshold set to be greater than overpopulation threshold" << std::endl
                                 << "underpopulation threshold: " << underpopulationThreshold << std::endl
                                 << "overpopulation threshold: " << overpopulationThreshold;
        throw Exception( ss.str() );
    }
    if( lowerReproductionThreshold>upperReproductionThreshold )
    {
        std::stringstream ss; ss << "[Rule::Rule] Error: Lower reproduction threshold set to be greater than upper reproduction threshold" << std::endl
                                 << "lower reproduction threshold: " << lowerReproductionThreshold << std::endl
                                 << "upper reproduction threshold: " << upperReproductionThreshold;
        throw Exception( ss.str() );
    }
}

// ----------------------------------------------------------------------------
Rule::~Rule()
{
}

} // namespace GOL
