/**
 * @file
 * @brief Define a metafunction to replace types.
 *
 * <pre>
 * 2-1. Write a ternary metafunction replace_type<c,x,y> that takes an arbitrary
 *      compound type c as its first parameter, and replaces all occurrences of a
 *      type x within c with y:
 *
 * typedef replace_type<void*,void, int>::type t1; // int*
 * typedef replace_type<
 *     int const*[10]
 *     , int const
 *     , long
 *     >::type t2; // long*[10]
 * typedef replace_type<
 *     char& (*)(char&)
 *     , char&
 *     , long&
 *     >::type t3; // long& (*)(long&)
 * </pre>
 *
 * @author Matt Bisson
 */

#ifndef EXERCISE_2_1
#define EXERCISE_2_1

#include <boost/type_traits/add_pointer.hpp>
#include <boost/type_traits/add_reference.hpp>

#include <boost/type_traits/is_same.hpp>

/**
 * @brief Given an arbitrary compound type, replace nested types.
 *
 * A ternary metafunction that takes an arbitrary compound type as its first
 * parameter, and replaces all occurrences of a given source type with a given
 * destination type.
 *
 * If X does not exist within C, this metafunction results in a compilation
 * error.
 *
 * @tparam C A compound type to examine for substitutions
 * @tparam X The source type to replace
 * @tparam Y The destination type to be placed where X was
 */
template <typename C, typename X, typename Y>
struct replace_type
{
    // If we missed a case, this should give an error about no "type"
};

/**
 * @brief Internal type used by replace_type.
 *
 * This type recurses through the datatype to do that actual replacement work.
 * The replace_type metafunction recurses down through any non-leaf types, and
 * this metafunction handles the leaf types.  Thus, if C == X, return Y, and
 * otherwise, we hand it back to replace_types.
 *
 * @tparam C A compound type to examine for substitutions
 * @tparam X The source type to replace
 * @tparam Y The destination type to be placed where X was
 * @tparam Same Does C == X?
 */
template <typename C, typename X, typename Y, bool Same>
struct replace_type_dispatch
{
    // Really a forward declaration.  "Same" specifications are given below.
};

/// @brief Descend through pointer types.
template <typename C, typename X, typename Y>
struct replace_type<C*, X, Y>
{
    typedef
    typename boost::add_pointer<
        typename replace_type_dispatch<
            C,
            X,
            Y,
            boost::is_same<C, X>::value
            >::type
        >::type
    type;
};

/// @brief Descend through reference types.
template <typename C, typename X, typename Y>
struct replace_type<C&, X, Y>
{
    typedef
    typename boost::add_reference<
        typename replace_type_dispatch<
            C,
            X,
            Y,
            boost::is_same<C, X>::value
            >::type
        >::type
    type;
};

/// @brief Descend through array types.
template <typename C, typename X, typename Y, size_t N>
struct replace_type<C[N], X, Y>
{
    typedef
    typename replace_type_dispatch<
        C,
        X,
        Y,
        boost::is_same<C, X>::value
        >::type
    type [N];
};

/// @brief Descent through nullary function types.
// Going to get tedious for multiple arguments... Could variadic templates help
// here?
template <typename Cr, typename X, typename Y>
struct replace_type<Cr(*)(), X, Y>
{
    typedef
    typename replace_type_dispatch<
        Cr,
        X,
        Y,
        boost::is_same<Cr, X>::value
        >::type
    (*type)();
};
/// @brief Descent through unary function types.
template <typename Cr, typename C0, typename X, typename Y>
struct replace_type<Cr(*)(C0), X, Y>
{
    typedef
    typename replace_type_dispatch<
        Cr,
        X,
        Y,
        boost::is_same<Cr, X>::value
        >::type
    (*type)(
        typename replace_type_dispatch<
            C0,
            X,
            Y,
            boost::is_same<C0, X>::value
            >::type
        );
};
/// @brief Descent through binary function types.
template <typename Cr, typename C0, typename C1, typename X, typename Y>
struct replace_type<Cr(*)(C0,C1), X, Y>
{
    typedef
    typename replace_type_dispatch<
        Cr,
        X,
        Y,
        boost::is_same<Cr, X>::value
        >::type
    (*type)(
        typename replace_type_dispatch<
            C0,
            X,
            Y,
            boost::is_same<C0, X>::value
            >::type,
        typename replace_type_dispatch<
            C1,
            X,
            Y,
            boost::is_same<C1, X>::value
            >::type
        );
};

/// @brief Replace leaf types.
template <typename C, typename X, typename Y>
struct replace_type_dispatch<C, X, Y, true>
{
    typedef Y type;
};
/// @brief Recurse into replace_type.
template <typename C, typename X, typename Y>
struct replace_type_dispatch<C, X, Y, false>
{
    typedef typename replace_type<C, X, Y>::type type;
};

#endif // EXERCISE_2_1
