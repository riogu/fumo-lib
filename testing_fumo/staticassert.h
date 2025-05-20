// clang-format off

/*
    Define macros to allow compile-time assertions.

    If the expression is false, an error something like

        test.c(9) : error XXXXX: negative subscript

    will be issued (the exact error and its format is dependent
    on the compiler).

    The techique used for C is to declare an extern (which can be used in
    file or block scope) array with a size of 1 if the expr is TRUE and
    a size of -1 if the expr is false (which will result in a compiler error).
    A counter or line number is appended to the name to help make it unique.  
    Note that this is not a foolproof technique, but compilers are
    supposed to accept multiple identical extern declarations anyway.

    This technique doesn't work in all cases for C++ because extern declarations
    are not permitted inside classes.  To get a CPP_ASSERT(), there is an 
    implementation of something similar to Boost's BOOST_STATIC_ASSERT().  Boost's
    approach uses template specialization; when expr evaluates to 1, a typedef
    for the type 

        ::interslice::StaticAssert_test< sizeof( ::interslice::StaticAssert_failed<true>) >

    which boils down to 

        ::interslice::StaticAssert_test< 1>

    which boils down to 

        struct StaticAssert_test

    is declared. If expr is 0, the compiler will be unable to find a specialization for

        ::interslice::StaticAssert_failed<false>.

    STATIC_ASSERT() or C_ASSERT should work in either C or C++ code  (and they do the same thing)

    CPP_ASSERT is defined only for C++ code.

    Since declarations can only occur at file scope or at the start of a block in 
    standard C, the C_ASSERT() or STATIC_ASSERT() macros will only work there.  For situations
    where you want to perform compile-time asserts elsewhere, use C_ASSERT_EX() or
    STATIC_ASSERT_X() which wrap an enum declaration inside it's own block.

 */

#ifndef C_ASSERT_H_3803b949_b422_4377_8713_ce606f29d546
#define C_ASSERT_H_3803b949_b422_4377_8713_ce606f29d546

/* first some utility macros to paste a line number or counter to the end of an identifier
 * this will let us have some chance of generating names that are unique
 * there may be problems if a static assert ends up on the same line number in different headers
 * to avoid that problem in C++ use namespaces
*/

#if !defined( PASTE)
#define PASTE2( x, y) x##y
#define PASTE( x, y)  PASTE2( x, y)
#endif /* PASTE */

#if !defined( PASTE_LINE)
#define PASTE_LINE( x)    PASTE( x, __LINE__)
#endif /* PASTE_LINE */

#if!defined( PASTE_COUNTER)
#if (_MSC_VER >= 1300)      /* __COUNTER__ introduced in VS 7 (VS.NET 2002) */
    #define PASTE_COUNTER( x) PASTE( x, __COUNTER__)   /* __COUNTER__ is a an _MSC_VER >= 1300 non-Ansi extension */
#else
    #define PASTE_COUNTER( x) PASTE( x, __LINE__)      /* since there's no __COUNTER__ use __LINE__ as a more or less reasonable substitute */
#endif
#endif /* PASTE_COUNTER */



#if __cplusplus
extern "C++" {   // required in case we're included inside an extern "C" block
    namespace interslice {
        template<bool b> struct StaticAssert_failed;
        template<>       struct StaticAssert_failed<true> { enum {val = 1 }; };
        template<int x>  struct StaticAssert_test { };
    }
}
    #define CPP_ASSERT( expr) typedef ::interslice::StaticAssert_test< sizeof( ::interslice::StaticAssert_failed< (bool) (expr) >) >  PASTE_COUNTER( IntersliceStaticAssertType_)
    #define STATIC_ASSERT( expr)    CPP_ASSERT( expr)
    #define STATIC_ASSERT_EX( expr) CPP_ASSERT( expr)
#else
    #define C_ASSERT_STORAGE_CLASS extern                  /* change to typedef might be needed for some compilers? */
    #define C_ASSERT_GUID 4964f7ac50fa4661a1377e4c17509495 /* used to make sure our extern name doesn't collide with something else */
    #define STATIC_ASSERT( expr)   C_ASSERT_STORAGE_CLASS char PASTE( PASTE( c_assert_, C_ASSERT_GUID), [(expr) ? 1 : -1])
    #define STATIC_ASSERT_EX(expr) do { enum { c_assert__ = 1/((expr) ? 1 : 0) }; } while (0)
#endif /* __cplusplus */

#if !defined( C_ASSERT)  /* C_ASSERT() might be defined by winnt.h */
#define C_ASSERT( expr)    STATIC_ASSERT( expr)
#endif /* !defined( C_ASSERT) */
#define C_ASSERT_EX( expr) STATIC_ASSERT_EX( expr)



#ifdef TEST_IMPLEMENTATION
C_ASSERT( 1 < 2);
C_ASSERT( 1 < 2);

int main( )
{
    C_ASSERT( 1 < 2);
    C_ASSERT( 1 < 2);

    int x;

    x = 1 + 4;

    C_ASSERT_EX( 1 < 2);
    C_ASSERT_EX( 1 < 2);



    return( 0);
}
#endif /* TEST_IMPLEMENTATION */
#endif /* C_ASSERT_H_3803b949_b422_4377_8713_ce606f29d546 */
