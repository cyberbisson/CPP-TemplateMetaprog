// ===-- chapter-5/exercise-5-9.hpp ----------------------- -*- C++ -*- --=== //
/**
 * @file
 * @brief Limit the max number of elements in the Fibonacci sequence.
 *
 * <pre>
 * 5-9. Modify the fibonacci_series sequence from exercise 5-8 to be limited by
 *      a maximum number of elements in the series. Make the sequence's
 *      iterators bidirectional:
 *
 * typedef fibonacci_series<8> seq;
 * BOOST_STATIC_ASSERT( mpl::size<seq>::value == 8 );
 * BOOST_STATIC_ASSERT( mpl::back<seq>::type::value == 13 );
 * </pre>
 *
 * @author Matt Bisson
 */

#ifndef EXERCISE_5_9
#define EXERCISE_5_9

#include "exercise-5-8.hpp"

/// @brief For a 32-bit signed integer, the max Fibonacci sequence seems to be
///        this.
static size_t const sMaxFibForInt32 = 45;

namespace boost {
namespace mpl {

/// @brief Establish an end (based on 32-bit signed int size).
template <>
struct next< fibonacci_series_iterator<1134903170, 701408733> >
{
    // Compilation error...
};

/// @brief Backward iteration is computable easily.
template <size_t N, size_t LastN>
struct prior< fibonacci_series_iterator<N, LastN> >
{
    typedef fibonacci_series_iterator<LastN, N-LastN> type;
};

/// @brief Special case because we chose an irregular "begin" iterator value.
template <> struct prior< fibonacci_series_iterator<1, 1> >
{
    typedef fibonacci_series_iterator<0, 1> type;
};

/// @brief Don't go before 0...
template <> struct prior< fibonacci_series_iterator<0, 1> >
{
    // Compilation error
};

} // namespace mpl
} // namespace boost

#endif // EXERCISE_5_9
