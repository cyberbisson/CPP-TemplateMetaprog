
/**
 * @file
 * @brief Chapter 3: A Deeper Look at Metafunctions
 *
 * C++ Template Metaprogramming: Concepts, Tools, and Techniques from Boost
 * and Beyond.
 *
 * @author Matt Bisson - 2/12/2014
 */

#include "exercise-3-0.hpp"
#include "exercise-3-1.hpp"
#include "exercise-3-2.hpp"
#include "exercise-3-3.hpp"
#include "exercise-3-4.hpp"
#include "exercise-3-5.hpp"
#include "exercise-3-6.hpp"

/**
 * @file
 *
 * Additional exercises:
 *
 * <pre>
 * 3-8. Our dimensional analysis framework dealt with dimensions, but it entirely
 *      ignored the issue of units.  A length can be represented in inches, feet,
 *      or meters.  A force can be represented in newtons or in kg m/sec^2.  Add
 *      the ability to specify units and test your code.  Try to make your
 *      interface as syntactically friendly as possible for the user.
 * </pre>
 */

// Add a units matrix to the quantity class-template that gets converted on
// every arithmetic operation?

int main()
{
    using namespace section_3_1;

    // Test simple addition
    {
        quantity<float, length> len1(1.0);
        quantity<float, length> len2(2.0);

        len1 = len1 + len2;
    }

    // Test multiplication
    {
        quantity<float, mass>         m(2.3);
        quantity<float, acceleration> a(0.3);

        quantity<float, force> f = m*a;
        f.value(); // Quiet the unused var warning w/o disabling it totally
    }

    // Test division
    {
        quantity<float, length> l(1.0);
        quantity<float, time>   s(3.0);

        quantity<float, velocity> v = l/s;
        v.value(); // Quiet the unused var warning w/o disabling it totally
    }

    // Exercise 3-4
    {
        quantity<float, force>        f(1.2);
        quantity<float, mass>         m(2.3);
        quantity<float, acceleration> a(0.3);

        f = f + m * a;
    }

    return 0;
}
