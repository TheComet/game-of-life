// --------------------------------------------------------------
// TestSignedArray2D.cpp
// --------------------------------------------------------------

// --------------------------------------------------------------
// include files

#include <gmock/gmock.h>
#include <SignedArray2D.hxx>
#include <exception>

// --------------------------------------------------------------
// define test fixtures

#define TEST_CASE_NAME TestSignedArray2D
#define TEST_CASE_OBJECT SignedArray2D<int>

TEST( TEST_CASE_NAME, ResizeAndDefaultFill )
{
    TEST_CASE_OBJECT test;
    test.resize(0, 0, 1, 1);
    ASSERT_EQ( 2, test.sizeX() );
    ASSERT_EQ( 2, test.sizeY() );
    ASSERT_EQ( 0, test.at(0,0) );
    ASSERT_EQ( 0, test.at(1,0) );
    ASSERT_EQ( 0, test.at(0,1) );
    ASSERT_EQ( 0, test.at(1,1) );

    test.resize(0, 0, 0, 0);
    ASSERT_EQ( 1, test.sizeX() );
    ASSERT_EQ( 1, test.sizeY() );

    test.resize(0, 0, 3, 0);
    ASSERT_EQ( 4, test.sizeX() );
    ASSERT_EQ( 1, test.sizeY() );
    ASSERT_EQ( 0, test.at(0,0) );
    ASSERT_EQ( 0, test.at(1,0) );
    ASSERT_EQ( 0, test.at(2,0) );
    ASSERT_EQ( 0, test.at(3,0) );
}

TEST( TEST_CASE_NAME, DefaultContentConstructor )
{
    TEST_CASE_OBJECT test(5);
    test.resize(0, 0, 1, 1);
    ASSERT_EQ( 5, test.at(0,0) );
    ASSERT_EQ( 5, test.at(1,0) );
    ASSERT_EQ( 5, test.at(0,1) );
    ASSERT_EQ( 5, test.at(1,1) );
}

TEST( TEST_CASE_NAME, CopyConstructor )
{
    TEST_CASE_OBJECT test;
    test.resize(0, 0, 1, 1);
    test.at(0,0) = 3;
    test.at(1,0) = 7;
    test.at(0,1) = 9;
    test.at(1,1) = 4;

    TEST_CASE_OBJECT copy( test );

    ASSERT_EQ( 3, copy.at(0,0) );
    ASSERT_EQ( 7, copy.at(1,0) );
    ASSERT_EQ( 9, copy.at(0,1) );
    ASSERT_EQ( 4, copy.at(1,1) );
}

TEST( TEST_CASE_NAME, Assignment )
{
    TEST_CASE_OBJECT test;
    test.resize(0, 0, 1, 1);
    test.at(0,0) = 3;
    test.at(1,0) = 7;
    test.at(0,1) = 9;
    test.at(1,1) = 4;

    TEST_CASE_OBJECT copy;
    copy = test;

    ASSERT_EQ( 3, copy.at(0,0) );
    ASSERT_EQ( 7, copy.at(1,0) );
    ASSERT_EQ( 9, copy.at(0,1) );
    ASSERT_EQ( 4, copy.at(1,1) );
}

TEST( TEST_CASE_NAME, CopyConstructorWithDefaultContent  )
{
    TEST_CASE_OBJECT test;
    test.resize(0, 0, 1, 1);
    test.at(0,0) = 3;
    test.at(1,0) = 7;
    test.at(0,1) = 9;
    test.at(1,1) = 4;

    TEST_CASE_OBJECT copy( test, 5 );
    copy.resize( 0, 0, 2, 1 );

    ASSERT_EQ( 3, copy.at(0,0) );
    ASSERT_EQ( 7, copy.at(1,0) );
    ASSERT_EQ( 9, copy.at(0,1) );
    ASSERT_EQ( 4, copy.at(1,1) );
    ASSERT_EQ( 5, copy.at(2,0) );
    ASSERT_EQ( 5, copy.at(2,1) );
}

TEST( TEST_CASE_NAME, SetAndGetDefaultContent )
{
    TEST_CASE_OBJECT test;
    test.setDefaultContent( 5 );
    test.resize(0, 0, 1, 1);
    ASSERT_EQ( 0, test.at(0,0) ); // element at 0,0 is already set during construction, and remains 0
    ASSERT_EQ( 5, test.at(1,0) );
    ASSERT_EQ( 5, test.at(0,1) );
    ASSERT_EQ( 5, test.at(1,1) );
    ASSERT_EQ( 5, test.getDefaultContent() );
}

TEST( TEST_CASE_NAME, MirrorX )
{
    TEST_CASE_OBJECT test;
    test.resize(0, 0, 1, 1);
    test.at(0,0) = 3;
    test.at(1,0) = 7;
    test.at(0,1) = 9;
    test.at(1,1) = 4;
    test.mirrorX();

    ASSERT_EQ( 7, test.at(0,0) );
    ASSERT_EQ( 3, test.at(1,0) );
    ASSERT_EQ( 4, test.at(0,1) );
    ASSERT_EQ( 9, test.at(1,1) );
}

TEST( TEST_CASE_NAME, MirrorY )
{
    TEST_CASE_OBJECT test;
    test.resize(0, 0, 1, 1);
    test.at(0,0) = 3;
    test.at(1,0) = 7;
    test.at(0,1) = 9;
    test.at(1,1) = 4;
    test.mirrorY();

    ASSERT_EQ( 9, test.at(0,0) );
    ASSERT_EQ( 4, test.at(1,0) );
    ASSERT_EQ( 3, test.at(0,1) );
    ASSERT_EQ( 7, test.at(1,1) );
}

TEST( TEST_CASE_NAME, AccessWithAt )
{
    TEST_CASE_OBJECT test;
    test.resize(0, 0, 0, 0);
    ASSERT_EQ( 0, test.at(0,0) );

    test.at(0,0) = 6;
    ASSERT_EQ( 6, test.at(0,0) );
}

TEST( TEST_CASE_NAME, NegativeResize )
{
    TEST_CASE_OBJECT test;
    test.resize( -4, -4, -3, -3 );
    ASSERT_EQ( 0, test.at(-4, -4 ) );
    ASSERT_EQ( 0, test.at(-4, -3 ) );
    ASSERT_EQ( 0, test.at(-3, -4 ) );
    ASSERT_EQ( 0, test.at(-3, -3 ) );
}

TEST( TEST_CASE_NAME, ExceptionOnIncorrectResize )
{
    TEST_CASE_OBJECT test;
    ASSERT_THROW( test.resize(3, 3, 2, 3), std::exception );
}

TEST( TEST_CASE_NAME, ExceptionOnOutOfBoundsAccess )
{
    TEST_CASE_OBJECT test;
    ASSERT_THROW( test.at(1,1), std::exception );
}
