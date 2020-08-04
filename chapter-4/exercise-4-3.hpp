// ===-- chapter-4/exercise-4-3.hpp ----------------------- -*- C++ -*- --=== //
/**
 * @file
 * @brief Weed out compile-time inefficiencies.
 *
 * <pre>
 * 4-3. Eliminate the unnecessary instantiations in the following code snippets:
 *
 * 1:
 * template <typename N, typename Predicate>
 * struct next_if
 *     : mpl::if_<
 *         typename mpl::apply<Predicate,N>::type,
 *         typename mpl::next<N>::type,
 *         N
 *     > { };
 *
 * 2:
 * template <typename N1, typename N2>
 * struct formula
 *     : mpl::if_<
 *         mpl::not_equal_to<N1,N2>,
 *         typename mpl::if_<
 *             mpl::greater<N1,N2>,
 *             typename mpl::minus<N1,N2>::type,
 *             N1
 *         >::type,
 *         typename mpl::plus<
 *             N1,
 *             typename mpl::multiplies< N1, mpl::int_<2> >::type
 *         >::type
 *     >::type
 * { };
 * </pre>
 *
 * @author Matt Bisson
 */

#ifndef EXERCISE_4_3
#define EXERCISE_4_3

#include <boost/static_assert.hpp>

#include <boost/mpl/apply.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/greater.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/minus.hpp>
#include <boost/mpl/multiplies.hpp>
#include <boost/mpl/not_equal_to.hpp>
#include <boost/mpl/plus.hpp>

#include <boost/mpl/placeholders.hpp>
using namespace boost::mpl::placeholders;

// Convenience used throughout the book's examples...
namespace mpl = boost::mpl;

/// @brief Fix algorithm 1 in Exercise 4-3:
template <typename N, typename Predicate>
struct next_if
    : mpl::eval_if<
        typename mpl::apply<Predicate, N>::type, // Why do I need ::type here?
        mpl::next<N>,
        mpl::identity<N>
    >::type
{ };

typedef next_if< mpl::int_<1>, mpl::greater<mpl::int_<0>, _1> > shouldBe1;
typedef next_if< mpl::int_<1>, mpl::greater<mpl::int_<3>, _1> > shouldBe2;

BOOST_STATIC_ASSERT((shouldBe1::value == 1));
BOOST_STATIC_ASSERT((shouldBe2::value == 2));

/// @brief Fix algorithm 2 in Exercise 4-3:
template <typename N1, typename N2>
struct formula
    : mpl::eval_if<
        mpl::not_equal_to<N1,N2>,
        mpl::eval_if<
            mpl::greater<N1,N2>,
            mpl::minus<N1,N2>,
            mpl::identity<N1> // Could skip identity...
        >,
        mpl::plus<
            N1,
            mpl::multiplies< N1, mpl::int_<2> >
        >
    >::type
{ };

typedef formula< mpl::int_<2>, mpl::int_<2> > shouldBe6;
typedef formula< mpl::int_<3>, mpl::int_<4> > shouldBe3;
typedef formula< mpl::int_<9>, mpl::int_<2> > shouldBe7;
BOOST_STATIC_ASSERT((shouldBe6::value == 6));
BOOST_STATIC_ASSERT((shouldBe3::value == 3));
BOOST_STATIC_ASSERT((shouldBe7::value == 7));

#endif // EXERCISE_4_3
