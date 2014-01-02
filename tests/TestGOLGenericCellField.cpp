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
/*
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
    TEST_CASE_OBJECT test(Rule(0,0,0,0));

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

*/
