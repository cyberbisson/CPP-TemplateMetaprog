/**
 * @file
 * @brief Iteratively call twice to add pointers to a type.
 *
 * <pre>
 * 3-4. Turn T into T**** using twice on itself.
 * </pre>
 *
 * @author Matt Bisson
 */

#ifndef EXERCISE_3_4
#define EXERCISE_3_4

#include "chapter-3-twice.hpp"

#include <boost/static_assert.hpp>

#include <boost/type_traits/add_pointer.hpp>

#include <boost/mpl/equal.hpp>
#include <boost/mpl/placeholders.hpp>
using namespace boost::mpl::placeholders;

/// @brief Call twice on itself to add four pointers to a type.
typedef twice<
    boost::add_pointer<_1>,
    twice< boost::add_pointer<_1>, int >::type
>::type double_twice;

BOOST_STATIC_ASSERT(
    (boost::mpl::equal<
     double_twice,
     int**** >::type::value));

#endif // EXERCISE_3_4
