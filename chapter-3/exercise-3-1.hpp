/**
 * @file
 * @brief Transform a vector by adding 1 to all its elements.
 *
 * <pre>
 * 3-1. Turn vector_c<int,1,2,3> into a type sequence with elements (2,3,4) using
 *      transform.
 * </pre>
 *
 * @author Matt Bisson
 */

#ifndef EXERCISE_3_1
#define EXERCISE_3_1

#include <boost/mpl/int.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/transform.hpp>

#include <boost/mpl/placeholders.hpp>
using namespace boost::mpl::placeholders;

/**
 * @brief Metafunction to apply during transformation.
 *
 * Basically this skirts around the issue of lazy function evaluation.  See
 * ex_3_1b for a better version.
 */
struct ex_3_1apply
{
    /// @brief Apply T+1
    template <typename T>
    struct apply : boost::mpl::plus< T, boost::mpl::int_<1> > { };
};

/**
 * @brief Add 1 to all items in a sequence (w/o placeholder args).
 * @tparam T The sequence to transform
 */
template <typename T>
struct ex_3_1 : boost::mpl::transform<T, ex_3_1apply > { };

/**
 * @brief Add 1 to all items in a sequence (w/ placeholder args).
 * @tparam T The sequence to transform
 */
template <typename T>
struct ex_3_1b
    : boost::mpl::transform<
        T,
        boost::mpl::plus< _1, boost::mpl::int_<1> >
        >
{ };

#ifndef SKIP_TEST

#include <boost/static_assert.hpp>

#include <boost/mpl/equal.hpp>
#include <boost/mpl/vector_c.hpp>

/// @brief Tests functionality from Exercise 3-1.
namespace ex_3_1ns
{
    typedef boost::mpl::vector_c<int, 1, 2, 3> init_vector_t;

    typedef ex_3_1<init_vector_t>::type new_vector_t;
    init_vector_t x;
    new_vector_t y;

    typedef ex_3_1b<init_vector_t>::type new_vectorb_t;
    new_vectorb_t z;

    BOOST_STATIC_ASSERT(
        (boost::mpl::equal<
         new_vectorb_t,
         boost::mpl::vector_c<int, 2, 3, 4> >::type::value));
}
#endif // SKIP_TEST

#endif // EXERCISE_3_1
