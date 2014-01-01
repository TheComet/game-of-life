// --------------------------------------------------------------
// TestGOLRule.cpp
// --------------------------------------------------------------

// --------------------------------------------------------------
// include files

#include <gmock/gmock.h>
#include <GOLRule.hpp>
#include <exception>

// --------------------------------------------------------------
// define test fixtures

#define TEST_CASE_NAME TestGOLRule
#define TEST_CASE_OBJECT Rule

using namespace GOL;

TEST( TEST_CASE_NAME, ConstructAndTestValues )
{
    TEST_CASE_OBJECT test( 2, 4, 7, 8 );
    ASSERT_EQ( 2, test.getUnderpopulationThreshold() );
    ASSERT_EQ( 4, test.getOverpopulationThreshold() );
    ASSERT_EQ( 7, test.getLowerReproductionThreshold() );
    ASSERT_EQ( 8, test.getUpperReproductionThreshold() );
}

TEST( TEST_CASE_NAME, ExceptionOnIncorrectPopulationThresholds )
{
    ASSERT_THROW( TEST_CASE_OBJECT(3,2,4,6), std::exception );
}

TEST( TEST_CASE_NAME, ExceptionOnIncorrectReproductionThresholds )
{
    ASSERT_THROW( TEST_CASE_OBJECT(2,3,6,4), std::exception );
}
