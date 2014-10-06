// --------------------------------------------------------------
// TestGOLCell.cpp
// --------------------------------------------------------------

// --------------------------------------------------------------
// include files

#include <gmock/gmock.h>
#include <GOLCell.hxx>
#include <exception>

// --------------------------------------------------------------
// define test fixtures

#define TEST_CASE_NAME TestGOLCell
#define TEST_CASE_OBJECT Cell<int>

using namespace GOL;

TEST( TEST_CASE_NAME, CoordinatesInConstructor )
{
    TEST_CASE_OBJECT test( 2 );
    ASSERT_EQ( 2, test.getCoordinate() );
}

TEST( TEST_CASE_NAME, SetAndGetCoordinates )
{
    TEST_CASE_OBJECT test;
    test.setCoordinate( 7 );
    ASSERT_EQ( 7, test.getCoordinate() );
}

TEST( TEST_CASE_NAME, link )
{
    TEST_CASE_OBJECT test, linkObj1, linkObj2, linkObj3;

    // link counts should all b e0
    ASSERT_EQ( 0, test.getLinkCount() );
    ASSERT_EQ( 0, linkObj1.getLinkCount() );
    ASSERT_EQ( 0, linkObj2.getLinkCount() );
    ASSERT_EQ( 0, linkObj3.getLinkCount() );

    // link test to three different nodes
    test.link( &linkObj1 );
    test.link( &linkObj2 );
    test.link( &linkObj3 );

    // test link count
    ASSERT_EQ( 3, test.getLinkCount() );
    ASSERT_EQ( 1, linkObj1.getLinkCount() );
    ASSERT_EQ( 1, linkObj2.getLinkCount() );
    ASSERT_EQ( 1, linkObj3.getLinkCount() );

    // test link pointers
    ASSERT_EQ( &test, linkObj1.getLinkedCell(0) );
    ASSERT_EQ( &test, linkObj2.getLinkedCell(0) );
    ASSERT_EQ( &test, linkObj3.getLinkedCell(0) );
    ASSERT_EQ( &linkObj1, test.getLinkedCell(0) );
    ASSERT_EQ( &linkObj2, test.getLinkedCell(1) );
    ASSERT_EQ( &linkObj3, test.getLinkedCell(2) );
}

TEST( TEST_CASE_NAME, unlink )
{
    TEST_CASE_OBJECT test, linkObj1, linkObj2, linkObj3;

    // link three nodes to "test", then unlink one of them
    test.link( &linkObj1 );
    test.link( &linkObj2 );
    test.link( &linkObj3 );
    test.unlink( &linkObj2 );

    // test link counts
    ASSERT_EQ( 2, test.getLinkCount() );
    ASSERT_EQ( 1, linkObj1.getLinkCount() );
    ASSERT_EQ( 0, linkObj2.getLinkCount() );
    ASSERT_EQ( 1, linkObj3.getLinkCount() );

    // test pointers
    ASSERT_EQ( &test, linkObj1.getLinkedCell(0) );
    ASSERT_EQ( &test, linkObj3.getLinkedCell(0) );
    ASSERT_EQ( &linkObj1, test.getLinkedCell(0) );
    ASSERT_EQ( &linkObj3, test.getLinkedCell(1) );
}

TEST( TEST_CASE_NAME, unlinkAll )
{
    TEST_CASE_OBJECT test, linkObj1, linkObj2, linkObj3;

    // link three nodes to "test", then unlink all
    test.link( &linkObj1 );
    test.link( &linkObj2 );
    test.link( &linkObj3 );
    test.unlinkAll();

    // test link counts
    ASSERT_EQ( 0, test.getLinkCount() );
    ASSERT_EQ( 0, linkObj1.getLinkCount() );
    ASSERT_EQ( 0, linkObj2.getLinkCount() );
    ASSERT_EQ( 0, linkObj3.getLinkCount() );
}

TEST( TEST_CASE_NAME, NodeLinkIDOutOfRangeException )
{
    TEST_CASE_OBJECT test, linkObj;
    test.link( &linkObj );

    // should throw an exception of provided ID is out of range
    ASSERT_NO_THROW( test.getLinkedCell(0) );
    ASSERT_THROW( test.getLinkedCell(1), std::exception );
}
