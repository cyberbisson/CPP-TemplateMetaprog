// ===-- chapter-6/chapter-6.cpp -------------------------- -*- C++ -*- --=== //
/**
 * @file
 * @brief Chapter 6: Algorithms
 *
 * C++ Template Metaprogramming: Concepts, Tools, and Techniques from Boost
 * and Beyond.
 *
 * @author Matt Bisson - 5/2/2014
 */

#include "exercise-6-0.hpp"
#include "exercise-6-1.hpp"
#include "exercise-6-3.hpp"
#include "exercise-6-4.hpp"

#include <stdio.h>

/**
 * @file
 *
 * Additional exercises:
 *
 * <pre>
 * 6-2. Because std::for_each is the most basic algorithm in the standard
 *      library, you may be wondering why we didn't say anything about its
 *      compile time counterpart.  The fact is that unlike, for example,
 *      transform, the algorithm does not have a pure compile time counterpart.
 *      Can you offer an explanation for that fact?
 * </pre>
 */

// Because C++ template metaprogramming does no have side-effects of any kind,
// the most useful forms of sequence traversal are either transforming one
// sequence into a copy, or visiting all arrays and accumulating a result.
// These are covered more concisely by the existing algorithms, without a need
// for a general purpose array traversal.

/**
 * @file
 *
 * <pre>
 * 6-5* List all algorithms in the standard library and compare their set to the
 *      set of algorithms provided by MPL. Analyze the differences.  What
 *      algorithms are named differently?  What algorithms have different
 *      semantics?  What algorithms are missing?  Why do you think they are
 *      missing?
 * </pre>
 */

int main()
{
#ifdef EXERCISE_6_1
    printf("Zero:  %i\n", zero);
    printf("One:   %i\n", one);
    printf("Three: %i\n", three);
    printf("Five:  %i\n", five);
    printf("Seven: %i\n", seven);
    printf("Nine:  %i\n", nine);
#endif

    return 0;
}
