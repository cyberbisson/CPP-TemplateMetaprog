// ===-- chapter-3/exercise-3-2.hpp ----------------------- -*- C++ -*- --=== //
/**
 * @file
 * @brief Square all elements in a sequence.
 *
 * <pre>
 * 3-2. Turn vector_c<int,1,2,3> into a type sequence with elements (1,4,9)
 *      using transform.
 * </pre>
 *
 * @author Matt Bisson
 */

#ifndef EXERCISE_3_2
#define EXERCISE_3_2

#include <boost/mpl/times.hpp>
#include <boost/mpl/transform.hpp>

#include <boost/mpl/placeholders.hpp>
using namespace boost::mpl::placeholders;

/**
 * @brief Given a sequence of numbers, return a sequence of their squares.
 * @tparam T The input sequence to transform
 */
template <typename T>
struct ex_3_2 : boost::mpl::transform< T, boost::mpl::times<_1, _1> > { };

#ifndef SKIP_TEST
#include <boost/static_assert.hpp>

#include <boost/mpl/equal.hpp>
#include <boost/mpl/vector_c.hpp>

/// @brief Tests functionality from Exercise 3-2.
namespace ex_3_2ns
{
    typedef boost::mpl::vector_c<int, 1, 2, 3> init_vector_t;

    typedef ex_3_2<init_vector_t>::type new_vector_t;
    new_vector_t x;

    BOOST_STATIC_ASSERT(
        (boost::mpl::equal<
         new_vector_t,
         boost::mpl::vector_c<int, 1, 4, 9> >::type::value));
}
#endif // SKIP_TEST

#endif // EXERCISE_3_2
