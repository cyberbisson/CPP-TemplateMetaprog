/**
 * @file
 * @brief Implement some new type traits with existing MPL facilities.
 *
 * <pre>
 * 4-4. Use integral operators and the type traits library facilities to
 *      implement the following composite traits:
 *          is_data_member_pointer
 *          is_pointer_to_function
 *          is_reference_to_function_pointer
 *          is_reference_to_non_const
 * </pre>
 *
 * @author Matt Bisson
 */

#ifndef EXERCISE_4_4
#define EXERCISE_4_4

#include <boost/static_assert.hpp>
#include <boost/type_traits.hpp> // Sledge-hammer of includes.

#include <boost/mpl/and.hpp>

/**
 * @brief Returns true if T is a pointer, but not a member function pointer.
 *
 * @tparam T The data-type to examine.
 */
template <typename T>
struct is_data_member_pointer
    : boost::mpl::and_<
        boost::is_member_pointer<T>,
        boost::mpl::not_< boost::is_member_function_pointer<T> >
    >
{ };

class test_class { };
BOOST_STATIC_ASSERT((is_data_member_pointer<int*(test_class::*)>::value));
BOOST_STATIC_ASSERT((!is_data_member_pointer<int*>::value));

/**
 * @brief Returns true if T is a pointer to a (non-member) function type.
 *
 * @tparam T The data-type to examine.
 */
template <typename T>
struct is_pointer_to_function
    : boost::mpl::and_<
        boost::is_pointer<T>,
        boost::is_function<typename boost::remove_pointer<T>::type>
    >
{ };

BOOST_STATIC_ASSERT((!is_pointer_to_function<void()>::value));
BOOST_STATIC_ASSERT((!is_pointer_to_function<void(*[])()>::value));
BOOST_STATIC_ASSERT((is_pointer_to_function<void(*)()>::value));
BOOST_STATIC_ASSERT((!is_pointer_to_function<int*>::value));
BOOST_STATIC_ASSERT((!is_pointer_to_function<int(*&)()>::value));
BOOST_STATIC_ASSERT((!is_pointer_to_function<int>::value));
BOOST_STATIC_ASSERT((!is_pointer_to_function<void(test_class::*)()>::value));

/**
 * @brief Returns true if T is a reference to a pointer to a (non-member)
 *     function!
 *
 * @tparam T The data-type to examine.
 */
template <typename T>
struct is_reference_to_function_pointer
    : boost::mpl::and_<
        boost::is_reference<T>,
        boost::is_pointer<typename boost::remove_reference<T>::type>,
        boost::is_function<
            typename boost::remove_pointer<
                typename boost::remove_reference<T>::type >::type >
    >
{ };

BOOST_STATIC_ASSERT((is_reference_to_function_pointer<void(*&)()>::value));
BOOST_STATIC_ASSERT((!is_reference_to_function_pointer<void(*)()>::value));
BOOST_STATIC_ASSERT((!is_reference_to_function_pointer<void(&)()>::value));
BOOST_STATIC_ASSERT((!is_reference_to_function_pointer<void()>::value));
BOOST_STATIC_ASSERT((!is_reference_to_function_pointer<int&>::value));
BOOST_STATIC_ASSERT((!is_reference_to_function_pointer<int*>::value));
BOOST_STATIC_ASSERT((!is_pointer_to_function<void(test_class::*&)()>::value));

/**
 * @brief Returns true if T is a reference type to a constant type.
 *
 * @tparam T The data-type to examine.
 */
template <typename T>
struct is_reference_to_non_const
    : boost::mpl::and_<
        boost::is_reference<T>,
        boost::mpl::not_<boost::is_const<
                             typename boost::remove_reference<T>::type>
        >
    >
{ };

BOOST_STATIC_ASSERT((!is_reference_to_non_const<int const>::value));
BOOST_STATIC_ASSERT((!is_reference_to_non_const<int const&>::value));
BOOST_STATIC_ASSERT((is_reference_to_non_const<int&>::value));

#endif // EXERCISE_4_4
