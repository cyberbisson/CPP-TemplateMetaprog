/**
 * @file
 * @brief Implement my versions of MPL boolean operations with many arguments.
 *
 * <pre>
 * 4-2. Extend the implementation of logical_or and logical_and metafunctions
 *      from exercise 4-1 to accept up to five arguments.
 * </pre>
 *
 * @author Matt Bisson
 */

#ifndef EXERCISE_4_2
#define EXERCISE_4_2

#include "chapter-4-undefined_bool.hpp"

#include <boost/static_assert.hpp>
#include <boost/mpl/bool.hpp>

/**
 * @brief Short-circuit logical OR evaluation for up to five boolean values.
 *
 * We're assuming that E1 has a boolean "value" member, but that it probably
 * isn't simply a boost::mpl::bool_ type.  Since the specializations operate on
 * bool_, we extract the value here, and pass it down throw a bool_.
 *
 * @tparam E1..E5 An expression that must at least have a boolean "value" member.
 */
template <
    typename E1,
    typename E2,
    typename E3 = boost::mpl::false_,
    typename E4 = boost::mpl::false_,
    typename E5 = boost::mpl::false_>
struct logical_or5
    : logical_or5<boost::mpl::bool_<E1::value>, E2, E3, E4, E5> { };

/// @brief Short-circuit on a true value.
template <typename E2, typename E3, typename E4, typename E5>
struct logical_or5<boost::mpl::true_, E2, E3, E4, E5>
{
    static bool const value = true;
};
/// @brief Pop/Evaluate the second value, putting false_ as the last parameter
template <typename E2, typename E3, typename E4, typename E5>
struct logical_or5<boost::mpl::false_, E2, E3, E4, E5>
    : logical_or5<
        boost::mpl::bool_<E2::value>, E2, E3, E4, boost::mpl::false_> { };

/// @brief If everything is a simple boost::mpl::false_ we can end recursion.
template <typename E5>
struct logical_or5<
    boost::mpl::false_,
    boost::mpl::false_,
    boost::mpl::false_,
    boost::mpl::false_,
    E5>
{
    static bool const value = E5::value;
};

BOOST_STATIC_ASSERT(
    (logical_or5<
     undefined_false<true>,
     undefined_false<false>
     >::value));
BOOST_STATIC_ASSERT(
    (logical_or5<
     boost::mpl::false_,
     boost::mpl::true_
     >::value));
BOOST_STATIC_ASSERT(
    (!logical_or5<
     boost::mpl::false_,
     boost::mpl::false_
     >::value));
BOOST_STATIC_ASSERT(
    (!logical_or5<
     boost::mpl::false_,
     boost::mpl::false_,
     boost::mpl::false_,
     boost::mpl::false_,
     boost::mpl::false_
     >::value));
BOOST_STATIC_ASSERT(
    (logical_or5<
     boost::mpl::false_,
     boost::mpl::false_,
     boost::mpl::false_,
     boost::mpl::false_,
     boost::mpl::true_
     >::value));
BOOST_STATIC_ASSERT(
    (logical_or5<
     undefined_false<true>,
     undefined_false<true>,
     undefined_false<true>,
     undefined_false<true>,
     undefined_false<false>
     >::value));

/**
 * @file
 * @todo Same logic holds true for logical_and, but with false_ instead of
 *     true_.  Go back and write logical_and some time.
 */

#endif // EXERCISE_4_2
