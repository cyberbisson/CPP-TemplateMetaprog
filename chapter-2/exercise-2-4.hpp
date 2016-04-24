/**
 * @file
 * @brief Print data-types using a home-grown solution.
 *
 * <pre>
 * 2-4. Write an alternative solution for exercise 2-3 that does not use the
 *      Type Traits library.  Compare the solutions.
 * </pre>
 *
 * @author Matt Bisson
 */

// Oops, turns out this was the obvious one for me...

#ifndef EXERCISE_2_4
#define EXERCISE_2_4

#include <iostream>

/**
 * @brief Print (a limited set of) data-types.
 *
 * When an instance of this type is streamed, the data-type of the template
 * parameter should be printed.
 *
 * @tparam T The data-type to describe to an output stream.
 *
 * @pre type_descriptor's template parameter is limited to compound types built
 *     from the following integral types: char, short int, int, and long int.
 *
 * @note The real work is done by free functions.  This allows us to claim
 *     almost no runtime overhead, as types are traversed recursively at compile
 *     time and printed directly without needing to build a run-time data
 *     strucutre.  Interestingly, I've asked this question on a few interviews,
 *     and people almost always try to construct a std::string member within
 *     type_descriptor for printing.
 */
template <typename T> struct type_descriptor { };

////////////////////////////////////////////////////////////////////////////////
// Non-leaf data-types:
////////////////////////////////////////////////////////////////////////////////

template <typename T>
std::ostream& operator<<(std::ostream& os, type_descriptor<T const> const&)
{
    return os << type_descriptor<T>() << " const";
}
template <typename T>
std::ostream& operator<<(std::ostream& os, type_descriptor<T&> const&)
{
    return os << type_descriptor<T>() << "&";
}
template <typename T>
std::ostream& operator<<(std::ostream& os, type_descriptor<T*> const&)
{
    return os << type_descriptor<T>() << "*";
}
template <typename T, size_t N>
std::ostream& operator<<(std::ostream& os, type_descriptor<T[N]> const&)
{
    return os << type_descriptor<T>() << "[" << N << "]";
}
template <typename T>
std::ostream& operator<<(std::ostream& os, type_descriptor<T()> const&)
{
    return os << type_descriptor<T>() << "()";
}
template <typename T>
std::ostream& operator<<(std::ostream& os, type_descriptor<T(*)()> const&)
{
    return os << type_descriptor<T>() << "(*)()";
}

////////////////////////////////////////////////////////////////////////////////
// Leaf data-types:
////////////////////////////////////////////////////////////////////////////////

std::ostream& operator<<(std::ostream& os, type_descriptor<char> const&)
{ return os << "char"; }
std::ostream& operator<<(std::ostream& os, type_descriptor<short> const&)
{ return os << "short int"; }
std::ostream& operator<<(std::ostream& os, type_descriptor<int> const&)
{ return os << "int"; }
std::ostream& operator<<(std::ostream& os, type_descriptor<long> const&)
{ return os << "long int"; }

#endif // EXERCISE_2_4
