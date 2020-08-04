
/**
 * @file
 * @brief Chapter 5: Sequences and Iterators
 *
 * C++ Template Metaprogramming: Concepts, Tools, and Techniques from Boost
 * and Beyond.
 *
 * @author Matt Bisson - 3/15/2014
 */

#include "chapter-5-tiny.hpp"
#include "exercise-5-1.hpp"
#include "exercise-5-6.hpp"
#include "exercise-5-7.hpp"
#include "exercise-5-8.hpp"
#include "exercise-5-9.hpp"
#include "exercise-5-10.hpp"

#include <stdio.h>

/**
 * @file
 *
 * Additional exercises:
 *
 * <pre>
 * 5-0. Write a test program that exercises the parts of tiny we've implemented.
 *      Try to arrange your program so that it will only compile if the tests
 *      succeed.
 * </pre>
 *
 * For exercises 5-2 through 5-5, see "chapter-5-tiny.hpp".
 */

/// @brief Tests for Exercise 5-0
void exercise_5_0()
{
#ifdef CHAPTER_5_TINY
    typedef tiny<int, char, float> v1;
    boost::mpl::deref< boost::mpl::begin<v1>::type >::type i1 = 5;
    boost::mpl::at< v1, boost::mpl::int_<1> >::type c1 = 'a';
    boost::mpl::deref<
        boost::mpl::prior< boost::mpl::end<v1>::type >::type
        >::type f1 = 2.5;

    printf("i1: (%lu,%i); c1: (%lu,%c); f1: (%lu,%f)\n",
           sizeof(i1), i1,
           sizeof(c1), c1,
           sizeof(f1), f1);

    typedef boost::mpl::clear<v1>::type v2;
    BOOST_STATIC_ASSERT((boost::is_same<v2::t0, none>::value));
    BOOST_STATIC_ASSERT((boost::is_same<v2::t1, none>::value));
    BOOST_STATIC_ASSERT((boost::is_same<v2::t2, none>::value));

    typedef boost::mpl::push_front<v2, double>::type v3;
    typedef boost::mpl::push_back<v3, int>::type v4;

    BOOST_STATIC_ASSERT((boost::mpl::equal< v4, tiny<double,int> >::value));
#endif
}

/// @brief Tests for Exercise 5-3
void exercise_5_3()
{
#ifdef CHAPTER_5_TINY
    typedef tiny<int> v1;
    BOOST_STATIC_ASSERT((boost::is_same<v1::t0, int>::value));
    BOOST_STATIC_ASSERT((boost::is_same<v1::t1, none>::value));
    BOOST_STATIC_ASSERT((boost::is_same<v1::t2, none>::value));
    BOOST_STATIC_ASSERT((boost::is_same<tiny<int>, v1>::value));

    typedef boost::mpl::insert<v1, boost::mpl::begin<v1>::type, float>::type v2;
    BOOST_STATIC_ASSERT((boost::is_same<tiny<float, int>, v2>::value));

    typedef boost::mpl::insert<v2, boost::mpl::end<v2>::type, char>::type v3;
    BOOST_STATIC_ASSERT((boost::is_same<tiny<float, int, char>, v3>::value));

    // Should be an error:
    // typedef typename boost::mpl::insert<
    //     v2, typename boost::mpl::end<v3>::type, char>::type v3;
#endif
}

/// @brief Tests for Exercise 5-5
void exercise_5_5()
{
#ifdef CHAPTER_5_TINY
    using namespace boost;
    using namespace boost::mpl;

    typedef tiny<int, float, char> v1;
    typedef begin<v1>::type  pos0;
    typedef next<pos0>::type pos1;
    typedef next<pos1>::type pos2;
    typedef end<v1>::type    posEnd;

    BOOST_STATIC_ASSERT((
        is_same< erase<v1, pos0>::type, tiny<float, char> >::value));
    BOOST_STATIC_ASSERT((
        is_same< erase<v1, pos1>::type, tiny<int, char> >::value));
    BOOST_STATIC_ASSERT((
        is_same< erase<v1, pos2>::type, tiny<int, float> >::value));

    BOOST_STATIC_ASSERT((
        is_same< erase<v1, pos0, pos1>::type, tiny<float, char> >::value));
    BOOST_STATIC_ASSERT((
        is_same< erase<v1, pos0, pos2>::type, tiny<char> >::value));
    BOOST_STATIC_ASSERT((
        is_same< erase<v1, pos0, posEnd>::type, tiny<> >::value));
    BOOST_STATIC_ASSERT((
        is_same< erase<v1, pos1, posEnd>::type, tiny<int> >::value));
    BOOST_STATIC_ASSERT((
        is_same< erase<v1, pos2, posEnd>::type, tiny<int, float> >::value));

    BOOST_STATIC_ASSERT((
        is_same< pop_front<v1>::type, tiny<float, char> >::value));
    BOOST_STATIC_ASSERT((
        is_same< pop_back<v1>::type, tiny<int, float> >::value));
#endif
}

/// @brief Tests for Exercise 5-6
void exercise_5_6()
{
#ifdef EXERCISE_5_6
    namespace mpl = boost::mpl;

    typedef dimensions<char[10][5][2]> seq;
    printf("%lu entries: (%lu, %lu, %lu)\n",
           mpl::size<seq>::value,
           mpl::at_c<seq,0>::type::value,
           mpl::at_c<seq,1>::type::value,
           mpl::at_c<seq,2>::type::value);


    // Note: I think the book's asserts are backwards.  I've changed the
    //       requirement.  See 5-7 for the list implemented as asked...
    BOOST_STATIC_ASSERT((mpl::size<seq>::value == 3));
    BOOST_STATIC_ASSERT((mpl::at_c<seq,0>::type::value == 10));
    BOOST_STATIC_ASSERT((mpl::at_c<seq,1>::type::value == 5));
    BOOST_STATIC_ASSERT((mpl::at_c<seq,2>::type::value == 2));
#endif
}

/// @brief Tests for Exercise 5-7
void exercise_5_7()
{
#ifdef EXERCISE_5_7
    namespace mpl = boost::mpl;

    typedef dimensions_b<int[10][5][2]> dim1;
    typedef mpl::begin<dim1>::type dim_it1;

    BOOST_STATIC_ASSERT((mpl::deref<dim_it1>::value == 2));

    printf("%lu entries: (%i, %i, %i)\n",
           mpl::size<dim1>::value,
           mpl::at_c<dim1,0>::type::value,
           mpl::at_c<dim1,1>::type::value,
           mpl::at_c<dim1,2>::type::value);

    BOOST_STATIC_ASSERT((mpl::size<dim1>::value == 3));
    BOOST_STATIC_ASSERT((mpl::at_c<dim1,0>::type::value == 2));
    BOOST_STATIC_ASSERT((mpl::at_c<dim1,1>::type::value == 5));
    BOOST_STATIC_ASSERT((mpl::at_c<dim1,2>::type::value == 10));

    typedef mpl::push_back< dim1, mpl::int_<3> >::type dim2;
    BOOST_STATIC_ASSERT((mpl::size<dim2>::value == 4));
    BOOST_STATIC_ASSERT((mpl::at_c<dim2,3>::type::value == 3));

    typedef mpl::pop_back<dim1>::type dim3;
    BOOST_STATIC_ASSERT((mpl::size<dim3>::value == 2));
#endif
}

#ifdef EXERCISE_5_9

/**
 * @brief Recursive Fibonacci sequence traversal via the print() method.
 *
 * As a test, here I'm going to print out all the Fibonacci numbers that a
 * 32-bit (signed) container can hold.
 *
 * @tparam CurFibIt Current iterator into the Fibonacci sequence.
 * @tparam Count    Iteration count (iteration stops at sMaxFibForInt32).
 */
template <typename CurFibIt, size_t Count>
struct print_fibonacci
{
    /// @brief The next number in the sequence
    typedef print_fibonacci<
        typename boost::mpl::next<CurFibIt>::type,
        Count+1> next;

    /// @brief Print the current Fibonacci number and kick off the next printout.
    void print() const
    {
        printf("%i ", boost::mpl::deref<CurFibIt>::type::value);
        next i;
        i.print();
    }
};

/// @brief Termination of Fibonacci sequence traversal.
template <typename CurFibIt>
struct print_fibonacci<CurFibIt, sMaxFibForInt32>
{
    /// @brief Print only the current Fibonacci number.
    void print() const
    {
        printf("%i ", boost::mpl::deref<CurFibIt>::type::value);
    }
};
#endif

/// @brief Give us a nice subroutine to tie Fibonacci seq printout all together.
void print_fibonacci_series()
{
#ifdef EXERCISE_5_9
    typedef print_fibonacci<
        boost::mpl::begin<fibonacci_series>::type,
        0
    > printer;

    printf("\nFibonacci: { ");
    {
        printer p;
        p.print();
    }
    printf("}\n");
#endif
}

int main()
{
    exercise_5_0();
    exercise_5_6();
    exercise_5_7();

    print_fibonacci_series();
    return 0;
}
