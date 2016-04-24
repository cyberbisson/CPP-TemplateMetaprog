
/**
 * @file
 * @brief Chapter 2: Traits and Type Manipulation
 *
 * C++ Template Metaprogramming: Concepts, Tools, and Techniques from Boost
 * and Beyond.
 *
 * @author Matt Bisson - 2/12/2014
 */

#include "exercise-2-0.hpp"
#include "exercise-2-1.hpp"
#include "exercise-2-2.hpp"
#include "exercise-2-3.hpp"
#include "exercise-2-4.hpp"
#include "exercise-2-5.hpp"

#include <cxxabi.h>

#include <iostream>
#include <typeinfo>

////////////////////////////////////////////////////////////////////////////////
// Testing / main()
////////////////////////////////////////////////////////////////////////////////

namespace {

struct TestA { virtual ~TestA() {} };
struct TestB : TestA {};

char const *demangle(char const *name)
{
    char   buf[1024];
    size_t size = 1024;
    int    status;

    char *res = abi::__cxa_demangle(
        name, buf, &size, &status);
    return res;
}

} // namespace <anon>

int main()
{
    std::cout << demangle(typeid(int*).name()) << "\n";

    // --- Exercise 2-0
#ifdef EXERCISE_2_0
    int z = 5;

//  int *const& a = &z;

    add_const_ref<int>::type x = z;
    add_const_ref<int&>::type y = z;
    std::cout << "Neither x: " << x << ", nor y: " << y << "are interesting.\n";

    std::cout <<
        boost::is_same<add_const_ref<int>::type, int const&>::value << "\n";
    std::cout <<
        boost::is_same<add_const_ref<int&>::type, int&>::value << "\n";
    std::cout <<
        boost::is_same<add_const_ref<int&>::type, int const&>::value << "\n";
    std::cout <<
        boost::is_same<
            add_const_ref<int const&>::type, int const&>::value << "\n";
    std::cout <<
        boost::is_same<
            add_const_ref<int const>::type, int const&>::value << "\n";

#endif

    // --- Exercise 2-1
#ifdef EXERCISE_2_1
    std::cout
        << boost::is_same<
            replace_type<void*, void, int>::type,
            int*>::value
        << "\n";
    std::cout
        << boost::is_same<
            replace_type<int const*[10], int const, long>::type,
            long*[10]>::value
        << "\n";
    std::cout
        << boost::is_same<
            replace_type<char& (*)(char&), char&, long&>::type,
               long& (*)(long&)>::value
        << "\n";
    // This is an error in the current design:
    // std::cout
    //     << boost::is_same<
    //         replace_type<char& (*)(char&), float, long&>::type,
    //            long& (*)(long&)>::value
    //     << "\n";
#endif

    // --- Exercise 2-2
#ifdef EXERCISE_2_2
    TestB b;
    TestA *a_ptr = &b;
    TestB *b_ptr = polymorphic_downcast<TestB*>(a_ptr);

    std::cout << "Address of b_ptr = " << static_cast<void*>(b_ptr) << "\n";

    TestA& a_ref = b;
    TestB& b_ref = polymorphic_downcast<TestB&>(a_ref);
#endif

    // --- Exercise 2-3
#ifdef EXERCISE_2_3

    // ************************** TO-DO
#endif

    // --- Exercise 2-4
#ifdef EXERCISE_2_4
    // prints "int"
    std::cout << type_descriptor<int>() << "\n";

    // prints "char*"
    std::cout << type_descriptor<char*>() << "\n";;

    // prints "short int[5]"
    std::cout << type_descriptor<short[5]>() << "\n";;

    // prints "long int const*&"
    std::cout << type_descriptor<long const*&>() << "\n";;

    // prints "char*()"
    std::cout << type_descriptor<char*()>() << "\n";;

    // prints "char*()"
    std::cout << type_descriptor<char*(*)()>() << "\n";;

    // --- Exercise 2-4
    std::cout << type_descriptor_eng<char*(*[])()>() << "\n";;
#endif
    return 0;
}
