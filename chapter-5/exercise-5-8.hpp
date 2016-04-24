/**
 * @file
 * @brief Write Fibonacci sequences with Boost MPL's sequence APIs.
 *
 * <pre>
 * 5-8. Write a fibonacci_series class that represents an infinite forward
 *      sequence of Fibonacci numbers:
 *
 * typedef mpl::advance_c<
 *     mpl::begin<fibonacci_series>::type, 6 >::type i;
 * BOOST_STATIC_ASSERT( mpl::deref<i>::type::value == 8 );
 *
 * typedef mpl::advance_c< i, 4 >::type j;
 * BOOST_STATIC_ASSERT( mpl::deref<j>::type::value == 55 );
 *
 *      Each element of the Fibonacci series is the sum of the previous two
 *      elements. The series begins 0, 1, 1, 2, 3, 5, 8, 13....
 * </pre>
 *
 * @author Matt Bisson
 */

#ifndef EXERCISE_5_8
#define EXERCISE_5_8

#include <boost/static_assert.hpp>

#include <boost/mpl/advance.hpp>
#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/iterator_tags.hpp>
#include <boost/mpl/next_prior.hpp>

/// @brief A tag for tag-dispatched sequence metafunctions.
struct fibonacci_series_tag { };

/**
 * @brief Iterator for moving through Fibonacci series sequence.
 *
 * This will hold all the data we need, really.
 *
 * @tparam N     The current "value".
 * @tparam LastN Our previous value will be added to the current one to get next.
 */
template <size_t N, size_t LastN>
struct fibonacci_series_iterator
{
    typedef boost::mpl::forward_iterator_tag category;
};

/// @brief The Fibonacci series for use with Boost MPL sequences.
struct fibonacci_series
{
    typedef fibonacci_series_tag tag;
};

namespace boost {
namespace mpl {

/// @brief Start with 1 in the "last" position so we don't waste time with 0+0.
template <>
struct begin_impl<fibonacci_series_tag>
{
    template <typename S>
    struct apply
    {
        typedef fibonacci_series_iterator<0, 1> type;
    };
};

/// @brief Make the new N the sum of both numbers; save the old N.
template <size_t N, size_t LastN>
struct next< fibonacci_series_iterator<N,LastN> >
{
    typedef fibonacci_series_iterator<N+LastN, N> type;
};

/// @brief Give us N.
template <size_t N, size_t LastN>
struct deref< fibonacci_series_iterator<N,LastN> > : boost::mpl::int_<N> { };

} // namespace mpl
} // namespace boost

typedef boost::mpl::advance_c<
    boost::mpl::begin<fibonacci_series>::type,
    6>::type i;
BOOST_STATIC_ASSERT(boost::mpl::deref<i>::type::value == 8);

typedef boost::mpl::advance_c<i, 4>::type j;
BOOST_STATIC_ASSERT(boost::mpl::deref<j>::type::value == 55);

#endif // EXERCISE_5_8
