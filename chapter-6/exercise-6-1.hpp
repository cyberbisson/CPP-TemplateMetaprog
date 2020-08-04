// ===-- chapter-6/exercise-6-1.hpp ----------------------- -*- C++ -*- --=== //
/**
 * @file
 * @brief Implement a binary to decimal converter as a sequence of binary
 *        digits.
 *
 * <pre>
 * 6-1. Rewrite the binary template from section 1.4.1 using one of the MPL
 *      sequence iteration algorithms, and write a test program that will only
 *      compile if your binary template is working.  Compare the amount of code
 *      you wrote with the version using handwritten recursion presented in
 *      Chapter 1.  What characteristics of the problem caused that result?
 * </pre>
 *
 * @author Matt Bisson
 */

#ifndef EXERCISE_6_1
#define EXERCISE_6_1

#include <boost/static_assert.hpp>

#include <boost/mpl/accumulate.hpp>
#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/iterator_tags.hpp>
#include <boost/mpl/next_prior.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/times.hpp>
using namespace boost::mpl::placeholders;

/// @brief A tag for tag-dispatched sequence metafunctions.
struct binary_tag { };

// Forward declaration for the benefit of the MPL sequence algorithms...
template <unsigned long N> struct binary;

namespace boost {
namespace mpl {

/// @brief Strip the least-significant binary digit from the number.
template <unsigned long N>
struct next< binary<N> >
{
    typedef binary<N/10> type;
};

/// @brief Algorithms require the full binary type for computations.
template <unsigned long N>
struct deref< binary<N> >
{
    typedef binary<N> type;
};

/// @brief Simply return the binary type as is.
template <>
struct begin_impl<binary_tag>
{
    template <typename T> struct apply { };

    template <unsigned long N>
    struct apply< binary<N> >
    {
        typedef binary<N> type;
    };
};

/// @brief When we have a value of 0, there are no more digits.
template <>
struct end_impl<binary_tag>
{
    template <typename T> struct apply { };

    template <unsigned long N>
    struct apply< binary<N> >
    {
        typedef binary<0> type;
    };
};

} // namespace mpl
} // namespace boost

/**
 * @brief Compile-time binary to decimal number translation.
 *
 * Technically, you can actually *traverse* binary<N> as a sequence with the
 * metafunctions, boost::mpl::begin, etc.  Each iterator wraps a single digit in
 * the binary number (0 or 1 -- no powers of 2 to indicate the significance of
 * the digit).
 *
 * @tparam N A binary number to examine.  Obvisouly, this should contain only 0
 *           and 1.
 */
template <unsigned long N>
struct binary
{
    typedef binary_tag tag;

    // Reverse iteration is trivial, but not useful at the moment.
    typedef boost::mpl::forward_iterator_tag category;

    /**
     * @brief Mathematics used by accumulate is broken out for clarity...
     *
     * @tparam T1 Our accumulated result so far.
     * @tparam T2 What remains of the binary number at this point in traversal.
     */
    template <typename T1, typename T2> struct apply_binary_digit { };

    /// @brief Specialization so we can get direct access to the binary numebr.
    template <typename T1, unsigned long N2>
    struct apply_binary_digit< T1, binary<N2> >
    {
        BOOST_STATIC_ASSERT((N2 % 10 < 2));
        typedef boost::mpl::plus<
            boost::mpl::times< T1, boost::mpl::int_<2> >,
            boost::mpl::int_<N2 % 10>
        > type;
    };

    /// @brief Iterate across the digits, building a decimal result.
    typedef typename boost::mpl::accumulate<
        binary<N>,
        boost::mpl::int_<0>,
        apply_binary_digit<_,_> >::type type;

    /// @brief The computed result as a constant value.
    static int const value = type::value;
};

unsigned const zero  = binary<0>::value;
unsigned const one   = binary<1>::value;
unsigned const three = binary<11>::value;
unsigned const five  = binary<101>::value;
unsigned const seven = binary<111>::value;
unsigned const nine  = binary<1001>::value;

// -- Compare the amount of code:
// This is a BOATLOAD more code.
//
// -- What characteristics of the problem caused that result?
// Really, this solution is only reasonable if one expects to traverse the
// individual digits in a binary number.  Since (as stated) the problem only
// takes a binary number input and returns a result, constructing the mechanics
// needed by a sequence algorithm to accumulate a (decimal) result is quite
// overkill.

#endif // EXERCISE_6_1
