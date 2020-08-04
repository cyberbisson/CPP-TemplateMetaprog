// ===-- chapter-2/exercise-2-5.hpp ----------------------- -*- C++ -*- --=== //
/**
 * @file
 * @brief Describe a data-type in English.
 *
 * <pre>
 * 2-5. Change the type_descriptor template from exercise 2-3 to output a
 *      pseudo-English description of the type, along the lines of the explain
 *      command of the cdecl program:
 *
 * // prints "array of pointer to function returning pointer to"
 * //        "char"
 * std::cout << type_descriptor< char *(*[])() >();
 * </pre>
 *
 * @author Matt Bisson
 */

#ifndef EXERCISE_2_5
#define EXERCISE_2_5

#include <iostream>

/**
 * @brief Display data-types in English wording.
 * @see type_descriptor
 */
template <typename T> struct type_descriptor_eng { };

////////////////////////////////////////////////////////////////////////////////
// Non-leaf data-types:
////////////////////////////////////////////////////////////////////////////////

template <typename T>
std::ostream& operator<<(std::ostream& os, type_descriptor_eng<T const> const&)
{
    return os << "const " << type_descriptor_eng<T>();
}
template <typename T>
std::ostream& operator<<(std::ostream& os, type_descriptor_eng<T&> const&)
{
    return os << "reference to " << type_descriptor_eng<T>();
}
template <typename T>
std::ostream& operator<<(std::ostream& os, type_descriptor_eng<T*> const&)
{
    return os << "pointer to " << type_descriptor_eng<T>();
}
template <typename T>
std::ostream& operator<<(std::ostream& os, type_descriptor_eng<T[]> const&)
{
    return os << "array of " << type_descriptor_eng<T>();
}
template <typename T, size_t N>
std::ostream& operator<<(std::ostream& os, type_descriptor_eng<T[N]> const&)
{
    return os << N << " element array of " << type_descriptor_eng<T>();
}
template <typename T>
std::ostream& operator<<(std::ostream& os, type_descriptor_eng<T()> const&)
{
    return os << "function returning " << type_descriptor_eng<T>();
}
template <typename T>
std::ostream& operator<<(std::ostream& os, type_descriptor_eng<T(*)()> const&)
{
    return os << "pointer to function returning " << type_descriptor_eng<T>();
}

////////////////////////////////////////////////////////////////////////////////
// Leaf data-types:
////////////////////////////////////////////////////////////////////////////////

std::ostream& operator<<(std::ostream& os, type_descriptor_eng<char> const&)
{ return os << "char"; }
std::ostream& operator<<(std::ostream& os, type_descriptor_eng<short> const&)
{ return os << "short int"; }
std::ostream& operator<<(std::ostream& os, type_descriptor_eng<int> const&)
{ return os << "int"; }
std::ostream& operator<<(std::ostream& os, type_descriptor_eng<long> const&)
{ return os << "long int"; }

#endif // EXERCISE_2_5
