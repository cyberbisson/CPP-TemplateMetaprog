// ===-- chapter-4/chapter-4.cpp -------------------------- -*- C++ -*- --=== //
/**
 * @file
 * @brief Chapter 4: Integral Type Wappers and Operators
 *
 * C++ Template Metaprogramming: Concepts, Tools, and Techniques from Boost
 * and Beyond.
 *
 * @author Matt Bisson - 2/28/2014
 */

#include "exercise-4-0.hpp"
#include "exercise-4-1.hpp"
#include "exercise-4-2.hpp"
#include "exercise-4-3.hpp"
#include "exercise-4-4.hpp"
#include "exercise-4-5.hpp"

#include <vector>

int main()
{
#ifdef EXERCISE_4_5
    std::vector<int> v;

    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);

    std::vector<int>::iterator it = container_find(v, 2);

    std::vector<int> const& v_ref = v;
    std::vector<int>::const_iterator it_const = container_find(v_ref, 2);
    printf("it %s it_const\n", (*it == *it_const) ? "==" : "!=");
#endif
    return 0;
}
