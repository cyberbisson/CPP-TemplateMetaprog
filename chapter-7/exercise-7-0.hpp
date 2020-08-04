// ===-- chapter-7/exercise-7-0.hpp ----------------------- -*- C++ -*- --=== //
/**
 * @file
 * @brief Use zip_view.
 *
 * <pre>
 * 7.0. Write a test program that exercises our zip_view implementation.  Try to
 *      arrange your program so that it will only compile if the tests succeed.
 * </pre>
 *
 * @author Matt Bisson
 */

#ifndef EXERCISE_7_0
#define EXERCISE_7_0

#include "chapter-7-zip_view.hpp"

#include <boost/static_assert.hpp>

#include <boost/mpl/copy.hpp>
#include <boost/mpl/back_inserter.hpp>
#include <boost/mpl/equal.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/vector_c.hpp>

/// @brief Namespace for testing in Exercise 7-0
namespace exercise_7_0 {

// We're going to test our ::zip_view by just smashing two vectors together,
// interleaving the results.  This doesn't test laziness, but does test
// correctness.

typedef boost::mpl::vector_c<int, 1, 3, 5, 7> v1;
typedef boost::mpl::vector_c<int, 2, 4, 6, 8> v2;
typedef boost::mpl::vector<v1, v2> zip_vec;

typedef boost::mpl::fold<
    ::zip_view<zip_vec>,
    boost::mpl::vector<>,
    boost::mpl::copy<_2, boost::mpl::back_inserter<_1> >
>::type folded;

typedef boost::mpl::vector_c<int, 1, 2, 3, 4, 5, 6, 7, 8> expected_results;
BOOST_STATIC_ASSERT((boost::mpl::equal<expected_results, folded>::value));

} // namespace exercise_7_0

#endif // EXERCISE_7_0
