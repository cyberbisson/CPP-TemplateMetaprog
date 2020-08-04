// ===-- chapter-4/exercise-4-5.hpp ----------------------- -*- C++ -*- --=== //
/**
 * @file
 * @brief Return different types based on parameter types.
 *
 * <pre>
 * 4-5. Consider the following function template, which is designed to provide a
 *      "container-based" (as opposed to iterator-based) interface to std::find:
 *          template <typename Container, typename Value>
 *          typename Container::iterator
 *          container_find(Container& c, Value const& v)
 *          {
 *              return std::find(c.begin(), c.end(), v);
 *          }
 *      As coded, container_find won't work for const containers; Container will
 *      be deduced as const X for some container type X, but when we try to
 *      convert the Container::const_iterator returned by std::find into a
 *      Container::iterator, compilation will fail.  Fix the problem using a
 *      small metaprogram to compute container_find's return type.
 * </pre>
 *
 * @author Matt Bisson
 */

#ifndef EXERCISE_4_5
#define EXERCISE_4_5

#include <algorithm>

#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_const.hpp>

/**
 * @brief Executes std::find across an entire container.
 *
 * This method is specially designed to return a const_iterator if the container
 * instance is constant, and non-const otherwise.
 *
 * @tparam Container The input container type.
 * @tparam Value     A value type suitable for the std::find algorithm when used
 *                   with Container type containers.
 *
 * @param[in] c The container to search.
 * @param[in] v The value to search for.
 *
 * @return An iterator to the position of the first element found to be
 *     equivalent to v.  The type is dynamically selected based on the container
 *     type.
 */
// I don't think eval_if buys you anything here, and you'd have to wrap the
// Container iterator types with boost::mpl::identity<T> in the "return" cases.
// The downside is that Container must have both const_iterator and iterator
// typedefs defined.
template <typename Container, typename Value>
typename boost::mpl::if_<
    boost::is_const<Container>,
    typename Container::const_iterator,
    typename Container::iterator>::type
container_find(Container& c, Value const& v)
{
    return std::find(c.begin(), c.end(), v);
}

#endif // EXERCISE_4_5
