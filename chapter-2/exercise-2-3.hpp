// ===-- chapter-2/exercise-2-3.hpp ----------------------- -*- C++ -*- --=== //
/**
 * @file
 * @brief Print data-types using Boost MPL.
 *
 * <pre>
 * 2-3. Use the type traits facilities to implement a type_descriptor class
 *      template, whose instances, when streamed, print the type of their
 *      template parameters:
 *
 * // prints "int"
 * std::cout << type_descriptor<int>();
 *
 * // prints "char*"
 * std::cout << type_descriptor<char*>();
 *
 * // prints "long const*&"
 * std::cout << type_descriptor<long const*&>();
 *
 *      You can assume that type_descriptor’s template parameter is limited to
 *      compound types built from the following four integral types: char,
 *      short int, int, and long int.
 * </pre>
 *
 * @author Matt Bisson
 */

#ifndef EXERCISE_2_3
#define EXERCISE_2_3

/**
 * @todo This seemed less interesting because I already did it (w/o Boost).
 *     We'll revisit when there's time.
 */
template <typename T>
struct type_descriptor2
{
    // std::ostream& operator<<(std::ostream& os)
};

#endif // EXERCISE_2_3
