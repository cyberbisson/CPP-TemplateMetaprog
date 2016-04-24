/**
 * @file
 * @brief Basic tests for MPL boolean operations.
 *
 * <pre>
 * 4-0. Write tests for mpl::or and mpl::and metafunctions that use their
 *      short-circuit behavior.
 * </pre>
 *
 * @author Matt Bisson
 */

#ifndef EXERCISE_4_0
#define EXERCISE_4_0

#include "chapter-4-undefined_bool.hpp"

#include <boost/static_assert.hpp>

#include <boost/mpl/and.hpp>
#include <boost/mpl/or.hpp>

// Check or_<true, fase> short-circuit.  If short-circuit doesn't work,
// undefined_false<false> will be checked; being undefined, this will be a
// compilation error.
BOOST_STATIC_ASSERT(
    (boost::mpl::or_< undefined_false<true>, undefined_false<false> >::value));

// Check and_<false, true> short-circuit.  If short-circuit doesn't work,
// undefined_false<false> will be checked; being undefined, this will be a
// compilation error.
BOOST_STATIC_ASSERT(
    (!boost::mpl::and_< undefined_true<false>, undefined_true<true> >::value));

#endif // EXERCISE_4_0
