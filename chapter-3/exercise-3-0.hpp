/**
 * @file
 * @brief Redefine the binary template to sanity-check its parameter.
 *
 * <pre>
 * 3-0. Use BOOST_STATIC_ASSERT to add error checking to the binary template
 *      presented in section 1.4.1, so that binary<N>::value causes a compilation
 *      error if N contains digits other than 0 or 1.
 * </pre>
 *
 * @author Matt Bisson
 */

#ifndef EXERCISE_3_0
#define EXERCISE_3_0

#include <boost/static_assert.hpp>

/**
 * @brief Compile-time binary to decimal number translation.
 * @tparam N A binary number to examine.  Obvisouly, this should contain only 0
 *           and 1.
 */
template <unsigned long N>
struct checked_binary
{
    BOOST_STATIC_ASSERT(((N % 10) < 2));

    static unsigned const value =
        (checked_binary<N/10>::value * 2) + (N % 10);
};

/// @brief Recursion termination
template<>
struct checked_binary<0>
{
    static unsigned const value = 0;
};

unsigned const one   = checked_binary<1>::value;
unsigned const three = checked_binary<11>::value;
unsigned const five  = checked_binary<101>::value;
unsigned const seven = checked_binary<111>::value;
unsigned const nine  = checked_binary<1001>::value;
//unsigned const bogus = checked_binary<2>::value; // Fails BOOST_STATIC_ASSERT

#endif // EXERCISE_3_0
