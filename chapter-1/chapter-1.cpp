
/**
 * @file
 * @brief Chapter 1: Introduction
 *
 * C++ Template Metaprogramming: Concepts, Tools, and Techniques from Boost
 * and Beyond.
 *
 * @author Matt Bisson - 2/12/2014
 */

#include <iostream>

/// @brief Code examples from the introduction
namespace chapter1 {

/**
 * @brief Prepend higher bits to lowest bit
 * @tparam N A binary number to examine.  Obvisouly, this should contain only 0
 *           and 1.
 */
template <unsigned long N>
struct binary
{
    static unsigned const value =
        (binary<N/10>::value * 2) + (N % 10);
};

/// @brief Recursion termination
template<>
struct binary<0>
{
    static unsigned const value = 0;
};

unsigned const one   = binary<1>::value;
unsigned const three = binary<11>::value;
unsigned const five  = binary<101>::value;
unsigned const seven = binary<111>::value;
unsigned const nine  = binary<1001>::value;

/**
 * @brief A runtime binary to decimal number translation.
 *
 * @param[in] N A binary number to examine.  Obvisouly, this should contain only
 *              0 and 1.
 * @return A decimal representation of the given binary number.
 */
unsigned binary_func(unsigned long N)
{
    return (N == 0) ? 0 : (N % 10) + (2 * binary_func(N/10));
}

} // namespace chapter1

int main()
{
    using namespace chapter1;

    std::cout << "Should be 1: " << one   << "\n";
    std::cout << "Should be 3: " << three << "\n";
    std::cout << "Should be 5: " << five  << "\n";
    std::cout << "Should be 7: " << seven << "\n";
    std::cout << "Should be 9: " << nine  << "\n";
    return 0;
}
