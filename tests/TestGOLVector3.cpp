// ----------------------------------------------------------------------------
// TestGOLVector3.cpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <gmock/gmock.h>
#include <GOLVector3.hxx>

// ----------------------------------------------------------------------------
// define test fixtures

#define TEST_CASE_NAME TestGOLVector3
#define TEST_CASE_OBJECT Vector3<float>

using namespace GOL;

TEST( TEST_CASE_NAME, DefaultConstructor )
{
    TEST_CASE_OBJECT test;
    ASSERT_EQ( 0.0f, test.x );
    ASSERT_EQ( 0.0f, test.y );
    ASSERT_EQ( 0.0f, test.z );
}

TEST( TEST_CASE_NAME, ConstructWithComponents )
{
    TEST_CASE_OBJECT test( 5.6f, 2.5f, 9.67f );
    ASSERT_EQ( 5.6f, test.x );
    ASSERT_EQ( 2.5f, test.y );
    ASSERT_EQ( 9.67f, test.z );
}

TEST( TEST_CASE_NAME, CompoundNormalise )
{
    TEST_CASE_OBJECT test( 2.0f, 3.0f, 6.0f );
    test.normalise();
    ASSERT_LE( 0.285713f, test.x );
    ASSERT_GE( 0.285715f, test.x );
    ASSERT_LE( 0.428570f, test.y );
    ASSERT_GE( 0.428572f, test.y );
    ASSERT_LE( 0.857141f, test.z );
    ASSERT_GE( 0.857143f, test.z );
}

TEST( TEST_CASE_NAME, NonCompoundNormalise )
{
    TEST_CASE_OBJECT test( 2.0f, 3.0f, 6.0f );
    TEST_CASE_OBJECT result = test.getNormalised();
    ASSERT_LE( 0.285713f, result.x );
    ASSERT_GE( 0.285715f, result.x );
    ASSERT_LE( 0.428570f, result.y );
    ASSERT_GE( 0.428572f, result.y );
    ASSERT_LE( 0.857141f, result.z );
    ASSERT_GE( 0.857143f, result.z );
    ASSERT_EQ( 2.0f, test.x );
    ASSERT_EQ( 3.0f, test.y );
    ASSERT_EQ( 6.0f, test.z );
}

TEST( TEST_CASE_NAME, DotProduct )
{
    TEST_CASE_OBJECT test( 2.0f, 6.0f, 5.0f );
    ASSERT_EQ( 65.0f, test.dot() );

    TEST_CASE_OBJECT other( 3.0f, 2.0f, 4.0f );
    ASSERT_EQ( 38.0f, test.dot(other) );
}

TEST( TEST_CASE_NAME, CompoundCrossProduct )
{
    TEST_CASE_OBJECT test( 2.0f, 3.0f, 4.0f );
    test.cross( TEST_CASE_OBJECT(5.0f, 7.0f, 9.0f) );

    ASSERT_EQ( -1.0f, test.x );
    ASSERT_EQ( 2.0f, test.y );
    ASSERT_EQ( -1.0f, test.z );
}

TEST( TEST_CASE_NAME, NonCompoundCrossProduct )
{
    TEST_CASE_OBJECT test( 2.0f, 3.0f, 4.0f );
    TEST_CASE_OBJECT result = test.getCross( TEST_CASE_OBJECT(5.0f, 7.0f, 9.0f) );

    ASSERT_EQ( -1.0f, result.x );
    ASSERT_EQ( 2.0f, result.y );
    ASSERT_EQ( -1.0f, result.z );
    ASSERT_EQ( 2.0f, test.x );
    ASSERT_EQ( 3.0f, test.y );
    ASSERT_EQ( 4.0f, test.z );
}

TEST( TEST_CASE_NAME, ComparisonOperators )
{
    TEST_CASE_OBJECT test1( 2.0f, 2.0f, 2.0f );
    TEST_CASE_OBJECT test2( 1.0f, 2.0f, 2.0f );

    ASSERT_NE( true, test1==test2 );
    ASSERT_EQ( true, test1!=test2 );
    ASSERT_EQ( true, test1> test2 );
    ASSERT_NE( true, test1< test2 );
    ASSERT_EQ( true, test1>=test2 );
    ASSERT_NE( true, test1<=test2 );
}

TEST( TEST_CASE_NAME, PlusPlusPrefix )
{
    TEST_CASE_OBJECT test( 2.0f, 4.0f, 6.0f );
    TEST_CASE_OBJECT check = ++test;

    ASSERT_EQ( 3.0f, test.x );
    ASSERT_EQ( 5.0f, test.y );
    ASSERT_EQ( 7.0f, test.z );
    ASSERT_EQ( 3.0f, check.x );
    ASSERT_EQ( 5.0f, check.y );
    ASSERT_EQ( 7.0f, check.z );
}

TEST( TEST_CASE_NAME, PlusPlusPostfix )
{
    TEST_CASE_OBJECT test( 2.0f, 4.0f, 6.0f );
    TEST_CASE_OBJECT check = test++;

    ASSERT_EQ( 3.0f, test.x );
    ASSERT_EQ( 5.0f, test.y );
    ASSERT_EQ( 7.0f, test.z );
    ASSERT_EQ( 2.0f, check.x );
    ASSERT_EQ( 4.0f, check.y );
    ASSERT_EQ( 6.0f, check.z );
}

TEST( TEST_CASE_NAME, MinusMinusPrefix )
{
    TEST_CASE_OBJECT test( 2.0f, 4.0f, 6.0f );
    TEST_CASE_OBJECT check = --test;

    ASSERT_EQ( 1.0f, test.x );
    ASSERT_EQ( 3.0f, test.y );
    ASSERT_EQ( 5.0f, test.z );
    ASSERT_EQ( 1.0f, check.x );
    ASSERT_EQ( 3.0f, check.y );
    ASSERT_EQ( 5.0f, check.z );
}

TEST( TEST_CASE_NAME, MinusMinusPostfix )
{
    TEST_CASE_OBJECT test( 2.0f, 4.0f, 6.0f );
    TEST_CASE_OBJECT check = test--;

    ASSERT_EQ( 1.0f, test.x );
    ASSERT_EQ( 3.0f, test.y );
    ASSERT_EQ( 5.0f, test.z );
    ASSERT_EQ( 2.0f, check.x );
    ASSERT_EQ( 4.0f, check.y );
    ASSERT_EQ( 6.0f, check.z );
}

TEST( TEST_CASE_NAME, NonCompoundAddition )
{
    TEST_CASE_OBJECT test( 2.0f, 4.0f, 6.0f );
    TEST_CASE_OBJECT result = test+TEST_CASE_OBJECT( 1.0f, 1.0f, 1.0f );

    ASSERT_EQ( 3.0f, result.x );
    ASSERT_EQ( 5.0f, result.y );
    ASSERT_EQ( 7.0f, result.z );
    ASSERT_EQ( 2.0f, test.x );
    ASSERT_EQ( 4.0f, test.y );
    ASSERT_EQ( 6.0f, test.z );
}

TEST( TEST_CASE_NAME, CompoundAddition )
{
    TEST_CASE_OBJECT test( 2.0f, 4.0f, 6.0f );
    test += TEST_CASE_OBJECT( 1.0f, 1.0f, 1.0f );

    ASSERT_EQ( 3.0f, test.x );
    ASSERT_EQ( 5.0f, test.y );
    ASSERT_EQ( 7.0f, test.z );
}

TEST( TEST_CASE_NAME, NonCompoundSubtraction )
{
    TEST_CASE_OBJECT test( 2.0f, 4.0f, 6.0f );
    TEST_CASE_OBJECT result = test-TEST_CASE_OBJECT( 1.0f, 1.0f, 1.0f );

    ASSERT_EQ( 1.0f, result.x );
    ASSERT_EQ( 3.0f, result.y );
    ASSERT_EQ( 5.0f, result.z );
    ASSERT_EQ( 2.0f, test.x );
    ASSERT_EQ( 4.0f, test.y );
    ASSERT_EQ( 6.0f, test.z );
}

TEST( TEST_CASE_NAME, CompoundSubtraction )
{
    TEST_CASE_OBJECT test( 2.0f, 4.0f, 6.0f );
    test -= TEST_CASE_OBJECT( 1.0f, 1.0f, 1.0f );

    ASSERT_EQ( 1.0f, test.x );
    ASSERT_EQ( 3.0f, test.y );
    ASSERT_EQ( 5.0f, test.z );
}
