// ----------------------------------------------------------------------------
// TestGOLCellField2D.cpp
// ----------------------------------------------------------------------------

// --------------------------------------------------------------
// include files

#include <gmock/gmock.h>
#include <GOLCellField2D.hpp>
#include <exception>

// --------------------------------------------------------------
// define test fixtures

#define TEST_CASE_NAME TestGOLCellFIeld2D
#define TEST_CASE_OBJECT CellField2D

using namespace GOL;

TEST( TEST_CASE_NAME, ConstructDefaultRules )
{
    TEST_CASE_OBJECT test;
    ASSERT_EQ( 2, test.getRule().getUnderpopulationThreshold() );
    ASSERT_EQ( 3, test.getRule().getOverpopulationThreshold() );
    ASSERT_EQ( 3, test.getRule().getLowerReproductionThreshold() );
    ASSERT_EQ( 3, test.getRule().getUpperReproductionThreshold() );
}

TEST( TEST_CASE_NAME, CalculateNextGenerationUsingDefault2DRules )
{
    TEST_CASE_OBJECT test;

    // add adjacent lookup table for 2D
    test.getAdjacentCellLookupTable().push_back( Vector2<int>(-1,-1) );
    test.getAdjacentCellLookupTable().push_back( Vector2<int>(-1,-0) );
    test.getAdjacentCellLookupTable().push_back( Vector2<int>(-1, 1) );
    test.getAdjacentCellLookupTable().push_back( Vector2<int>( 0,-1) );
    test.getAdjacentCellLookupTable().push_back( Vector2<int>( 0, 1) );
    test.getAdjacentCellLookupTable().push_back( Vector2<int>( 1,-1) );
    test.getAdjacentCellLookupTable().push_back( Vector2<int>( 1, 0) );
    test.getAdjacentCellLookupTable().push_back( Vector2<int>( 1, 1) );

    // create R-pentomino for testing purposes
    test.addCell( Vector2<int>(-1, 0) );
    test.addCell( Vector2<int>( 0,-1) );
    test.addCell( Vector2<int>( 0, 0) );
    test.addCell( Vector2<int>( 0, 1) );
    test.addCell( Vector2<int>( 1,-1) );

    /* below are the first three generations (0-2)
          **
         **
          *

         ***
         *
         **

          *
         **
        *  *
         **
    */

    // advance one generation
    test.calculateNextGeneration();

    // test pattern in a 5x5 block
    ASSERT_NE( true, test.isCellAlive(Vector2<int>(-2,-2)) );
    ASSERT_NE( true, test.isCellAlive(Vector2<int>(-1,-2)) );
    ASSERT_NE( true, test.isCellAlive(Vector2<int>( 0,-2)) );
    ASSERT_NE( true, test.isCellAlive(Vector2<int>( 1,-2)) );
    ASSERT_NE( true, test.isCellAlive(Vector2<int>( 2,-2)) );

    ASSERT_NE( true, test.isCellAlive(Vector2<int>(-2,-1)) );
    ASSERT_EQ( true, test.isCellAlive(Vector2<int>(-1,-1)) );
    ASSERT_EQ( true, test.isCellAlive(Vector2<int>( 0,-1)) );
    ASSERT_EQ( true, test.isCellAlive(Vector2<int>( 1,-1)) );
    ASSERT_NE( true, test.isCellAlive(Vector2<int>( 2,-1)) );

    ASSERT_NE( true, test.isCellAlive(Vector2<int>(-2, 0)) );
    ASSERT_EQ( true, test.isCellAlive(Vector2<int>(-1, 0)) );
    ASSERT_NE( true, test.isCellAlive(Vector2<int>( 0, 0)) );
    ASSERT_NE( true, test.isCellAlive(Vector2<int>( 1, 0)) );
    ASSERT_NE( true, test.isCellAlive(Vector2<int>( 2, 0)) );

    ASSERT_NE( true, test.isCellAlive(Vector2<int>(-2, 1)) );
    ASSERT_EQ( true, test.isCellAlive(Vector2<int>(-1, 1)) );
    ASSERT_EQ( true, test.isCellAlive(Vector2<int>( 0, 1)) );
    ASSERT_NE( true, test.isCellAlive(Vector2<int>( 1, 1)) );
    ASSERT_NE( true, test.isCellAlive(Vector2<int>( 2, 1)) );

    ASSERT_NE( true, test.isCellAlive(Vector2<int>(-2, 2)) );
    ASSERT_NE( true, test.isCellAlive(Vector2<int>(-1, 2)) );
    ASSERT_NE( true, test.isCellAlive(Vector2<int>( 0, 2)) );
    ASSERT_NE( true, test.isCellAlive(Vector2<int>( 1, 2)) );
    ASSERT_NE( true, test.isCellAlive(Vector2<int>( 2, 2)) );

    // advance another generation
    test.calculateNextGeneration();

    // test pattern in a 5x5 block
    ASSERT_NE( true, test.isCellAlive(Vector2<int>(-2,-2)) );
    ASSERT_NE( true, test.isCellAlive(Vector2<int>(-1,-2)) );
    ASSERT_EQ( true, test.isCellAlive(Vector2<int>( 0,-2)) );
    ASSERT_NE( true, test.isCellAlive(Vector2<int>( 1,-2)) );
    ASSERT_NE( true, test.isCellAlive(Vector2<int>( 2,-2)) );

    ASSERT_NE( true, test.isCellAlive(Vector2<int>(-2,-1)) );
    ASSERT_EQ( true, test.isCellAlive(Vector2<int>(-1,-1)) );
    ASSERT_EQ( true, test.isCellAlive(Vector2<int>( 0,-1)) );
    ASSERT_NE( true, test.isCellAlive(Vector2<int>( 1,-1)) );
    ASSERT_NE( true, test.isCellAlive(Vector2<int>( 2,-1)) );

    ASSERT_EQ( true, test.isCellAlive(Vector2<int>(-2, 0)) );
    ASSERT_NE( true, test.isCellAlive(Vector2<int>(-1, 0)) );
    ASSERT_NE( true, test.isCellAlive(Vector2<int>( 0, 0)) );
    ASSERT_EQ( true, test.isCellAlive(Vector2<int>( 1, 0)) );
    ASSERT_NE( true, test.isCellAlive(Vector2<int>( 2, 0)) );

    ASSERT_NE( true, test.isCellAlive(Vector2<int>(-2, 1)) );
    ASSERT_EQ( true, test.isCellAlive(Vector2<int>(-1, 1)) );
    ASSERT_EQ( true, test.isCellAlive(Vector2<int>( 0, 1)) );
    ASSERT_NE( true, test.isCellAlive(Vector2<int>( 1, 1)) );
    ASSERT_NE( true, test.isCellAlive(Vector2<int>( 2, 1)) );

    ASSERT_NE( true, test.isCellAlive(Vector2<int>(-2, 2)) );
    ASSERT_NE( true, test.isCellAlive(Vector2<int>(-1, 2)) );
    ASSERT_NE( true, test.isCellAlive(Vector2<int>( 0, 2)) );
    ASSERT_NE( true, test.isCellAlive(Vector2<int>( 1, 2)) );
    ASSERT_NE( true, test.isCellAlive(Vector2<int>( 2, 2)) );

}
