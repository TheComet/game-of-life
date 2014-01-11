// --------------------------------------------------------------
// TestGOLGenericCellField.cpp
// --------------------------------------------------------------

// --------------------------------------------------------------
// include files

#include <gmock/gmock.h>
#include <GOLGenericCellField.hxx>
#include <exception>

// --------------------------------------------------------------
// define test fixtures

#define TEST_CASE_NAME TestGOLGenericCellFIeld
#define TEST_CASE_OBJECT GenericCellField<int>

using namespace GOL;

TEST( TEST_CASE_NAME, ConstructWithRules )
{
    TEST_CASE_OBJECT test( Rule(4,6,5,7) );
    ASSERT_EQ( 4, test.getRule().getUnderpopulationThreshold() );
    ASSERT_EQ( 6, test.getRule().getOverpopulationThreshold() );
    ASSERT_EQ( 5, test.getRule().getLowerReproductionThreshold() );
    ASSERT_EQ( 7, test.getRule().getUpperReproductionThreshold() );
}

TEST( TEST_CASE_NAME, AddAndRemoveCells )
{
    TEST_CASE_OBJECT test( Rule(0,0,0,0) );

    test.addCell(1);
    test.addCell(6);
    test.addCell(9);

    ASSERT_NE( true, test.isCellAlive(3) );
    test.addCell( 3 );
    ASSERT_EQ( true, test.isCellAlive(3) );
    test.removeCell( 3 );
    ASSERT_NE( true, test.isCellAlive(3) );
    ASSERT_EQ( true, test.isCellAlive(1) );
    ASSERT_EQ( true, test.isCellAlive(6) );
    ASSERT_EQ( true, test.isCellAlive(9) );
}

TEST( TEST_CASE_NAME, CalculateNextGenerationIn1D )
{
    TEST_CASE_OBJECT test( Rule(1,1,2,2) );

    // add adjacent lookup table for 2D
    test.getAdjacentCellLookupTable().push_back( -1 );
    test.getAdjacentCellLookupTable().push_back(  1 );

    // create R-pentomino for testing purposes
    test.addCell( -1 );
    test.addCell(  0 );
    test.addCell(  2 );
    test.addCell(  4 );
    test.addCell(  5 );

    ASSERT_EQ( 5, test.getActiveCellList().size() );

    /* below are the first three generations (0-2)
        ** * **

        *** ***

        * *** *
    */

    // advance one generation
    test.calculateNextGeneration();

    // test size
    ASSERT_EQ( 6, test.getActiveCellList().size() );

    // test pattern in a 5x5 block
    ASSERT_NE( true, test.isCellAlive( -2 ) );
    ASSERT_EQ( true, test.isCellAlive( -1 ) );
    ASSERT_EQ( true, test.isCellAlive(  0 ) );
    ASSERT_EQ( true, test.isCellAlive(  1 ) );
    ASSERT_NE( true, test.isCellAlive(  2 ) );
    ASSERT_EQ( true, test.isCellAlive(  3 ) );
    ASSERT_EQ( true, test.isCellAlive(  4 ) );
    ASSERT_EQ( true, test.isCellAlive(  5 ) );
    ASSERT_NE( true, test.isCellAlive(  6 ) );

    // advance another generation
    test.calculateNextGeneration();

    // test size
    ASSERT_EQ( 5, test.getActiveCellList().size() );

    // test pattern in a 5x5 block
    ASSERT_NE( true, test.isCellAlive( -2 ) );
    ASSERT_EQ( true, test.isCellAlive( -1 ) );
    ASSERT_NE( true, test.isCellAlive(  0 ) );
    ASSERT_EQ( true, test.isCellAlive(  1 ) );
    ASSERT_EQ( true, test.isCellAlive(  2 ) );
    ASSERT_EQ( true, test.isCellAlive(  3 ) );
    ASSERT_NE( true, test.isCellAlive(  4 ) );
    ASSERT_EQ( true, test.isCellAlive(  5 ) );
    ASSERT_NE( true, test.isCellAlive(  6 ) );

}
