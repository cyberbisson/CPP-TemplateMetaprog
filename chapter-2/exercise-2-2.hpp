/**
 * @file
 * @brief Rewrite boost::polymorphic_downcast.
 *
 * <pre>
 * 2-2. The boost::polymorphic_downcast function template implements a checked
 *      version of static_cast intended for downcasting pointers to polymorphic
 *      objects:
 *
 *      In released software, the assertion disappears and polymorphic_downcast
 *      can be as efficient as a simple static_cast.  Use the type traits
 *      facilities to write an implementation of the template that allows both
 *      pointer and reference arguments.
 * </pre>
 *
 * @author Matt Bisson
 */

#ifndef EXERCISE_2_2
#define EXERCISE_2_2

#include <assert.h>

#include <boost/type_traits/add_pointer.hpp>

/**
 * @brief Check the validity of a downcast.
 *
 * This method asserts (in debug builds only) that the downcast was legal.  This
 * overload accepts a pointer type.
 *
 * @tparam Target The resulting type of the cast.
 * @tparam Source The input datatype (wihtout pointer).  Do not specify this
 *     explicitly: it should be deduced by the compiler.
 *
 * @param[in] x An input pointer type.
 * @return A dynamically casted instance from the source type.
 */
template <typename Target, typename Source>
inline Target polymorphic_downcast(Source *x)
{
    assert(dynamic_cast<Target>(x) == x);
    return static_cast<Target>(x);
}

/**
 * @brief Check the validity of a downcast.
 *
 * This method asserts (in debug builds only) that the downcast was legal.  This
 * overload accepts a reference type.
 *
 * @tparam Target The resulting type of the cast.
 * @tparam Source The input datatype (wihtout reference).  Do not specify this
 *     explicitly: it should be deduced by the compiler.
 *
 * @param[in] x An input reference type.
 * @return A dynamically casted instance from the source type.
 */
template <typename Target, typename Source>
inline Target polymorphic_downcast(Source& x)
{
    // Should assert that Target is a reference...

    assert(
        dynamic_cast<
            typename boost::add_pointer<
                typename boost::remove_reference<Target>::type
            >::type>(&x)
        == &x);
    return static_cast<Target>(x);
}

#endif // EXERCISE_2_2
