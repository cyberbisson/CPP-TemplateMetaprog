// ===-- chapter-2/exercise-2-0.hpp ----------------------- -*- C++ -*- --=== //
/**
 * @file
 * @brief Define a metafunction to add const&.
 *
 * <pre>
 * 2-0. Write a unary metafunction add_const_ref<T> that returns T if it is a
 *      reference type, and otherwise returns T const&.  Write a program to test
 *      your metafunction.  Hint: you can use boost::is_same to test the
 *      results.
 * </pre>
 *
 * @author Matt Bisson
 */

#ifndef EXERCISE_2_0
#define EXERCISE_2_0

#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/add_reference.hpp>

/**
 * @brief Contains a set of solutions implemented without the aid of the
 * Boost MPL.
 *
 * Occasionally it is more interesting / efficient to tackle problems on your
 * own.  There will likely be a corresponding set implemented without.
 *
 * @see with_boost
 */
namespace no_boost {

/**
 * @brief The default implementation adds a const& to the template type.
 *
 * Specializations are all partial, and specialize based on the IsRef parameter.
 *
 * If IsRef is true, this simply returns the template parameter, unmodified.
 *
 * @tparam T     The datatype to alter.
 * @tparam IsRef A boolean value that should be true if T is already a reference
 *               type.
 */
template <typename T, bool IsRef>
struct add_const_ref_impl
{
    typedef T const& type;
};
/// @brief Simply return the original type if we're already a reference type.
template <typename T>
struct add_const_ref_impl<T, true>
{
    typedef T type;
};

/**
 * @brief This is a home-grown implementation to the problem.
 * @see ::add_const_ref
 */
template <typename T>
struct add_const_ref : add_const_ref_impl<T, false> { };

/// @brief Partial specialization for when T is already a reference.
template <typename T>
struct add_const_ref<T&> : add_const_ref_impl<T&, true> { };

/// @brief (Paranoia) Strip off const on T const to avoid T const const&.  Not
/// required.
template <typename T>
struct add_const_ref<T const> : add_const_ref_impl<T, false> { };

} // namespace no_boost


/**
 * @brief Contains a set of solutions implemented with Boost MPL.
 *
 * There will likely be a corresponding set implemented without.
 *
 * @see no_boost
 */
namespace with_boost {

/**
 * @brief Boost MPL implementation.
 * @see ::add_const_ref
 */
template <typename T>
struct add_const_ref
{
    // For int&, add_const has no effect, then add_reference does nothing as
    // it's already a reference type.
    typedef typename boost::add_reference<
        typename boost::add_const<T>::type
    >::type type;
};

} // with_boost

/**
 * @brief A unary metafunction that returns T if it is a reference type, and
 * otherwise returns T const&.
 *
 * @tparam T The type to check and modify.
 */
template<typename T>
struct add_const_ref : no_boost::add_const_ref<T> { };

#endif // EXERCISE_2_0
