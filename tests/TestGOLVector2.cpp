// ----------------------------------------------------------------------------
// TestGOLVector2.cpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <gmock/gmock.h>
#include <GOLVector2.hxx>

// ----------------------------------------------------------------------------
// define test fixtures

#define TEST_CASE_NAME TestGOLVector2
#define TEST_CASE_OBJECT Vector2<float>

using namespace GOL;

TEST( TEST_CASE_NAME, DefaultConstructor )
{
    TEST_CASE_OBJECT test;
    ASSERT_EQ( 0.0f, test.x );
    ASSERT_EQ( 0.0f, test.y );
}

TEST( TEST_CASE_NAME, ConstructWithComponents )
{
    TEST_CASE_OBJECT test( 5.6f, 2.5f );
    ASSERT_EQ( 5.6f, test.x );
    ASSERT_EQ( 2.5f, test.y );
}

TEST( TEST_CASE_NAME, DotProduct )
{
    TEST_CASE_OBJECT test( 2.0f, 6.0f );
    ASSERT_EQ( 40.0f, test.dot() );

    TEST_CASE_OBJECT other( 3.0f, 2.0f );
    ASSERT_EQ( 18.0f, test.dot(other) );
}

TEST( TEST_CASE_NAME, ComparisonOperators )
{
    TEST_CASE_OBJECT test1( 2.0f, 2.0f );
    TEST_CASE_OBJECT test2( 1.0f, 2.0f );

    ASSERT_NE( true, test1==test2 );
    ASSERT_EQ( true, test1!=test2 );
    ASSERT_EQ( true, test1> test2 );
    ASSERT_NE( true, test1< test2 );
    ASSERT_EQ( true, test1>=test2 );
    ASSERT_NE( true, test1<=test2 );
}
