// ----------------------------------------------------------------------------
// TestGOLVector3.cpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <gmock/gmock.h>
#include <GOLSortedList.hxx>

// ----------------------------------------------------------------------------
// define test fixtures

#define TEST_CASE_NAME TestGOLSortedList
#define TEST_CASE_OBJECT SortedList<int>

using namespace GOL;

TEST( TEST_CASE_NAME, ConstructAndDestruct )
{
    TEST_CASE_OBJECT* test = new TEST_CASE_OBJECT();
    ASSERT_EQ( 0, test->size() );
    ASSERT_EQ( 0, test->allocatedSize() );
    delete test;
}

TEST( TEST_CASE_NAME, ConstructWithPreallocatedMemory )
{
    TEST_CASE_OBJECT test(10);
    ASSERT_EQ( 10, test.size() );
    ASSERT_EQ( 10, test.allocatedSize() );
    for( std::size_t n = 0; n != test.size(); ++n )
        ASSERT_EQ( 0, test[n] );
}

TEST( TEST_CASE_NAME, InsertItemsAndGetItems )
{
    TEST_CASE_OBJECT test;
    test.insert(4);
    test.insert(7);
    test.insert(2);
    test.insert(9);
    test.insert(6);
    test.insert(5);
    test.insert(10);
    test.insert(1);
    test.insert(3);
    test.insert(8);

    ASSERT_EQ( 1, test.at(0) );
    ASSERT_EQ( 2, test.at(1) );
    ASSERT_EQ( 3, test.at(2) );
    ASSERT_EQ( 4, test.at(3) );
    ASSERT_EQ( 5, test.at(4) );
    ASSERT_EQ( 6, test.at(5) );
    ASSERT_EQ( 7, test.at(6) );
    ASSERT_EQ( 8, test.at(7) );
    ASSERT_EQ( 9, test.at(8) );
    ASSERT_EQ( 10, test.at(9) );
}

TEST( TEST_CASE_NAME, EraseWithIndex )
{
    TEST_CASE_OBJECT test;
    test.insert(5);
    test.insert(3);
    test.insert(7);
    test.insert(9);

    test.erase(2);

    ASSERT_EQ( 3, test.size() );
    ASSERT_EQ( 4, test.allocatedSize() );
    ASSERT_EQ( 3, test.at(0) );
    ASSERT_EQ( 5, test.at(1) );
    ASSERT_EQ( 9, test.at(2) );
}

TEST( TEST_CASE_NAME, EraseWithIterator )
{
    TEST_CASE_OBJECT test;
    test.insert(5);
    test.insert(3);
    test.insert(7);
    test.insert(9);

    test.erase( test.begin()+2 );

    ASSERT_EQ( 3, test.size() );
    ASSERT_EQ( 4, test.allocatedSize() );
    ASSERT_EQ( 3, test.at(0) );
    ASSERT_EQ( 5, test.at(1) );
    ASSERT_EQ( 9, test.at(2) );
}

TEST( TEST_CASE_NAME, FindInsertPosition )
{
    TEST_CASE_OBJECT test;
    test.insert(1);
    test.insert(2);
    test.insert(6);
    test.insert(7);

    ASSERT_EQ( 0, test.findInsertPosition(0) );
    ASSERT_EQ( 0, test.findInsertPosition(1) );
    ASSERT_EQ( 1, test.findInsertPosition(2) );
    ASSERT_EQ( 2, test.findInsertPosition(3) ); // next greater item is returned
    ASSERT_EQ( 2, test.findInsertPosition(4) ); // next greater item is returned
    ASSERT_EQ( 2, test.findInsertPosition(5) ); // next greater item is returned
    ASSERT_EQ( 2, test.findInsertPosition(6) );
    ASSERT_EQ( 3, test.findInsertPosition(7) );
    ASSERT_EQ( 4, test.findInsertPosition(8) );
    ASSERT_EQ( 4, test.findInsertPosition(9) );
}

TEST( TEST_CASE_NAME, FindItem )
{
    TEST_CASE_OBJECT test;
    test.insert(1);
    test.insert(2);
    test.insert(5);
    test.insert(6);

    ASSERT_EQ( test.end(), test.find(0) );
    ASSERT_EQ( 1, *test.find(1) );
    ASSERT_EQ( 2, *test.find(2) );
    ASSERT_EQ( test.end(), test.find(3) );
    ASSERT_EQ( test.end(), test.find(4) );
    ASSERT_EQ( 5, *test.find(5) );
    ASSERT_EQ( 6, *test.find(6) );
    ASSERT_EQ( test.end(), test.find(7) );
}

TEST( TEST_CASE_NAME, ClearItemsAndCheckAllocatedMemory )
{
    TEST_CASE_OBJECT test;
    test.insert(1);
    test.insert(6);
    test.insert(3);
    test.insert(10);
    test.clear();

    ASSERT_EQ( 0, test.size() );
    ASSERT_EQ( 4, test.allocatedSize() );

    test.insert(5);
    test.insert(3);
    test.insert(4);
    ASSERT_EQ( 3, test.size() );
    ASSERT_EQ( 4, test.allocatedSize() );
    ASSERT_EQ( 3, test.at(0) );
    ASSERT_EQ( 4, test.at(1) );
    ASSERT_EQ( 5, test.at(2) );

    test.insert(9);
    test.insert(0);
    ASSERT_EQ( 5, test.size() );
    ASSERT_EQ( 5, test.allocatedSize() );
    ASSERT_EQ( 0, test.at(0) );
    ASSERT_EQ( 3, test.at(1) );
    ASSERT_EQ( 4, test.at(2) );
    ASSERT_EQ( 5, test.at(3) );
    ASSERT_EQ( 9, test.at(4) );
}

TEST( TEST_CASE_NAME, ResizeAndCheckAllocatedMemory )
{
    TEST_CASE_OBJECT test;
    test.insert(1);
    test.insert(6);
    test.insert(3);
    test.insert(10);

    // resize larger
    test.resize(6);
    ASSERT_EQ( 6, test.size() );
    ASSERT_EQ( 6, test.allocatedSize() );
    ASSERT_EQ( 0, test.at(4) );
    ASSERT_EQ( 0, test.at(5) );

    // test insertion
    test.insert(11);
    test.insert(13);
    test.insert(12);
    ASSERT_EQ( 9, test.size() );
    ASSERT_EQ( 9, test.allocatedSize() );
    ASSERT_EQ( 11, test.at(6) );
    ASSERT_EQ( 12, test.at(7) );
    ASSERT_EQ( 13, test.at(8) );

    // resize smaller
    test.resize(2);
    ASSERT_EQ( 2, test.size() );
    ASSERT_EQ( 2, test.allocatedSize() );
    ASSERT_EQ( 1, test.at(0) );
    ASSERT_EQ( 3, test.at(1) );

    // data should have been deleted when resizing larger again
    test.resize(4);
    ASSERT_EQ( 4, test.size() );
    ASSERT_EQ( 4, test.allocatedSize() );
    ASSERT_EQ( 0, test.at(2) );
    ASSERT_EQ( 0, test.at(3) );
}

TEST( TEST_CASE_NAME, Iterator )
{
    TEST_CASE_OBJECT test;
    test.insert(2);
    test.insert(4);
    test.insert(3);

    int x=2;
    for( TEST_CASE_OBJECT::iterator it = test.begin(); it != test.end(); ++it )
    {
        ASSERT_EQ( x, *it );
        ++x;
    }
}

TEST( TEST_CASE_NAME, ConstIterator )
{
    TEST_CASE_OBJECT test;
    test.insert(2);
    test.insert(4);
    test.insert(3);

    int x=2;
    for( TEST_CASE_OBJECT::const_iterator it = test.begin(); it != test.end(); ++it )
    {
        ASSERT_EQ( x, *it );
        ++x;
    }
}

TEST( TEST_CASE_NAME, CopyConstructor )
{
    TEST_CASE_OBJECT test;
    test.insert(4);
    test.insert(7);
    test.insert(9);

    TEST_CASE_OBJECT copy(test);
    ASSERT_EQ( 3, test.size() );
    ASSERT_EQ( 3, test.allocatedSize() );
    ASSERT_EQ( 4, test.at(0) );
    ASSERT_EQ( 7, test.at(1) );
    ASSERT_EQ( 9, test.at(2) );
}

TEST( TEST_CASE_NAME, AssignmentWithLargerRValue )
{
    TEST_CASE_OBJECT test;
    test.insert(4);
    test.insert(7);
    test.insert(9);

    TEST_CASE_OBJECT copy;
    copy.insert(3);
    copy.insert(1);
    copy.insert(2);
    copy.insert(8);
    copy.insert(5);

    copy = test;

    ASSERT_EQ( 3, test.size() );
    ASSERT_EQ( 3, test.allocatedSize() );
    ASSERT_EQ( 4, test.at(0) );
    ASSERT_EQ( 7, test.at(1) );
    ASSERT_EQ( 9, test.at(2) );
}

TEST( TEST_CASE_NAME, AssignmentWithSmallerRValue )
{
    TEST_CASE_OBJECT test;
    test.insert(4);
    test.insert(7);
    test.insert(9);

    TEST_CASE_OBJECT copy;
    copy.insert(3);
    copy.insert(1);

    copy = test;

    ASSERT_EQ( 3, test.size() );
    ASSERT_EQ( 3, test.allocatedSize() );
    ASSERT_EQ( 4, test.at(0) );
    ASSERT_EQ( 7, test.at(1) );
    ASSERT_EQ( 9, test.at(2) );
}

TEST( TEST_CASE_NAME, SubscriptOperator )
{
    TEST_CASE_OBJECT test;
    test.insert(4);
    test.insert(7);
    test.insert(9);
    ASSERT_EQ( 4, test[0] );
    ASSERT_EQ( 7, test[1] );
    ASSERT_EQ( 9, test[2] );
}

TEST( TEST_CASE_NAME, ConstSubscriptOperator )
{
    TEST_CASE_OBJECT test;
    test.insert(4);
    test.insert(7);
    test.insert(9);

    const int a = test[0];
    const int b = test[1];
    const int c = test[2];

    ASSERT_EQ( a, test[0] );
    ASSERT_EQ( b, test[1] );
    ASSERT_EQ( c, test[2] );
}

TEST( TEST_CASE_NAME, EraseExceptionOnIndexOutOfBounds )
{
    TEST_CASE_OBJECT test;
    test.insert(1);
    test.insert(2);

    ASSERT_THROW( test.erase(2), std::exception );
    ASSERT_NO_THROW( test.erase(std::size_t(0)) );
    ASSERT_THROW( test.erase(1), std::exception );
    ASSERT_NO_THROW( test.erase(std::size_t(0)) );
    ASSERT_THROW( test.erase(std::size_t(0)), std::exception );
}

TEST( TEST_CASE_NAME, AtExceptionOnIndexOutOfBounds )
{
    TEST_CASE_OBJECT test;
    test.insert(1);
    test.insert(2);

    ASSERT_THROW( test.at(2), std::exception );
    ASSERT_NO_THROW( test.at(0) );
    ASSERT_NO_THROW( test.at(1) );
}
