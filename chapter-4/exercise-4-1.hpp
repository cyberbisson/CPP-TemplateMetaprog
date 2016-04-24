/**
 * @file
 * @brief Implement my own versions of Boost MPL boolean operations.
 *
 * <pre>
 * 4-1. Implement binary metafunctions called logical_or and logical_and that
 *      model the behavior of mpl::or_ and mpl::and_, correspondingly.  Use
 *      tests from exercise 4-0 to verify your implementation.
 * </pre>
 *
 * @author Matt Bisson
 */

#ifndef EXERCISE_4_1
#define EXERCISE_4_1

#include "chapter-4-undefined_bool.hpp"

#include <boost/static_assert.hpp>
#include <boost/mpl/bool.hpp>

/**
 * @brief Short-circuit logical OR evaluation of two boolean values.
 *
 * We're assuming that E1 has a boolean "value" member, but that it probably
 * isn't simply a boost::mpl::bool_ type.  Since the specializations operate on
 * bool_, we extract the value here, and pass it down throw a bool_.
 *
 * @tparam E1 An expression that must at least have a boolean "value" member.
 * @tparam E2 An expression that must at least have a boolean "value" member.
 */
template <typename E1, typename E2>
struct logical_or : logical_or<boost::mpl::bool_<E1::value>, E2> { };

/// @brief Short-circuit on a true value
template <typename E2>
struct logical_or<boost::mpl::true_, E2>
{
    static bool const value = true;
};
/// @brief If the first value is false, the result is whatever E2's value is.
template <typename E2>
struct logical_or<boost::mpl::false_, E2>
{
    static bool const value = E2::value;
};

BOOST_STATIC_ASSERT(
    (logical_or< undefined_false<true>, undefined_false<false> >::value));
BOOST_STATIC_ASSERT(
    (logical_or< boost::mpl::false_, boost::mpl::true_ >::value));
BOOST_STATIC_ASSERT(
    (!logical_or< boost::mpl::false_, boost::mpl::false_ >::value));

/**
 * @brief Short-circuit logical OR evaluation of two boolean values.
 *
 * We're assuming that E1 has a boolean "value" member, but that it probably
 * isn't simply a boost::mpl::bool_ type.  Since the specializations operate on
 * bool_, we extract the value here, and pass it down throw a bool_.
 *
 * @tparam E1 An expression that must at least have a boolean "value" member.
 * @tparam E2 An expression that must at least have a boolean "value" member.
 */
template <typename E1, typename E2>
struct logical_and : logical_and<boost::mpl::bool_<E1::value>, E2> { };

/// @brief Short-circuit on a true value.
template <typename E2>
struct logical_and<boost::mpl::false_, E2>
{
    static bool const value = false;
};
/// @brief If the first value is true, the result is whatever E2's value is.
template <typename E2>
struct logical_and<boost::mpl::true_, E2>
{
    static bool const value = E2::value;
};

BOOST_STATIC_ASSERT(
    (!logical_and< undefined_true<false>, undefined_true<true> >::value));
BOOST_STATIC_ASSERT(
    (!logical_and< boost::mpl::true_, boost::mpl::false_ >::value));
BOOST_STATIC_ASSERT(
    (logical_and< boost::mpl::true_, boost::mpl::true_ >::value));

#endif // EXERCISE_4_1
