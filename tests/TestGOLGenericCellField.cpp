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

TEST( TEST_CASE_NAME, AddAndRemoveCell )
{
    TEST_CASE_OBJECT test;

    test.addCell(1);
    test.addCell(6);
    test.addCell(9);

    ASSERT_NE( true, test.isCellAlive(3) );
    test.addCell( 3 );
    ASSERT_EQ( true, test.isCellAlive(3) );
    test.removeCell( 3 );
    ASSERT_NE( true, test.isCellAlive(3) );
}
