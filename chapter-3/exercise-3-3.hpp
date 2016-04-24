/**
 * @file
 * @brief Manipulate pointers with the twice metafunction.
 *
 * <pre>
 * 3-3. Turn T into T**** by using twice twice.
 * </pre>
 *
 * @author Matt Bisson
 */

#ifndef EXERCISE_3_3
#define EXERCISE_3_3

#include "chapter-3-twice.hpp"

#include <boost/static_assert.hpp>

#include <boost/type_traits/add_pointer.hpp>

#include <boost/mpl/equal.hpp>
#include <boost/mpl/placeholders.hpp>
using namespace boost::mpl::placeholders;

/// @brief Used twice to add two pointers.
typedef twice<boost::add_pointer<_1>, int>::type double_pointer_int;
BOOST_STATIC_ASSERT(
    (boost::mpl::equal<
     double_pointer_int,
     int** >::type::value));

/// @brief Used twice twice to add four pointers.
typedef twice<boost::add_pointer<_1>, double_pointer_int>::type four_pointer_int;
BOOST_STATIC_ASSERT(
    (boost::mpl::equal<
     four_pointer_int,
     int**** >::type::value));

#endif // EXERCISE_3_3
