/**
 * @file
 * @brief Provide bi-directional iterators to Exercise 5-6.
 *
 * <pre>
 * 5-7. Modify the dimensions sequence adapter from exercise 5-6 to provide
 *      bidirectional iterators and push_back and pop_back operations.
 * </pre>
 *
 * @author Matt Bisson
 */

#ifndef EXERCISE_5_7
#define EXERCISE_5_7

#include "exercise-5-6.hpp"

#include <boost/mpl/pop_back.hpp>
#include <boost/mpl/push_back.hpp>

/// @brief A tag for tag-dispatched sequence metafunctions.
struct dimensions_b_tag { };

/// @brief Define a bi-directional iterator for our dimensions_b sequence.
template <typename S>
struct dimensions_b_iterator
{
    typedef boost::mpl::bidirectional_iterator_tag category;
};

/**
 * @brief Implement the dimensions_b sequence.
 * @note This non-specialized version should only be used for a non-array T type
 *       (i.e., an empty list).
 *
 * @tparam T    The compound array type to examine.
 * @tparam Next The next item in the sequence (saved as we build the sequence).
 */
template <typename T, typename Next>
struct dimensions_b_impl
    : boost::mpl::void_
{
    typedef dimensions_b_tag tag;

    typedef boost::mpl::void_ next;
    typedef boost::mpl::void_ prev;
};

/**
 * @brief Descend through the T types, removing an array each time.
 *
 * This results in a list in the correct order, but held fron the back...
 */
template <typename T, size_t N, typename Next>
struct dimensions_b_impl<T[N], Next>
    : boost::mpl::int_<N>
{
    typedef dimensions_b_tag tag;

    typedef Next next;
    typedef typename
        boost::mpl::if_<
            boost::is_array<T>,
            dimensions_b_impl< T, dimensions_b_impl<T[N], Next> >,
            boost::mpl::void_
        >::type prev;
};

/**
 * @brief Represent the dimensions in an array type as a sequence of numbers.
 *
 * The dimensions sequence is a recursively defined sequence that strips off a
 * single array dimension as you advance through the sequence.  The recently
 * stripped dimension exists as a static member (value).
 *
 * @note The outward-facing metafunction simply forwards to the implementation
 *       class
 *
 * @tparam T The (compound) array type to examine.  If T is not an array type,
 *           the sequence is not traverse-able.
 */
template <typename T>
struct dimensions_b : dimensions_b_impl<T, boost::mpl::void_> { };

/**
 * @brief begin_impl_traversal walks the list to find the beginning
 *
 * This is where the real sequence construction occurs.  Declaring the sequence
 * does no work, but finding the beginning realizes the entire sequence by
 * invoking S::prev until we find the "beginning" (i.e., boost::mpl::void_).
 *
 * @tparam S      The sequence (in reality, just the back).
 * @tparam S_Prev The part of the sequence immediately preceeding S.
 */
template <typename S, typename S_Prev>
struct begin_impl_traversal
    : begin_impl_traversal<S_Prev, typename S_Prev::prev> { };

/// @brief We've found the beginning.
template <typename S>
struct begin_impl_traversal<S, boost::mpl::void_>
{
    typedef S type;
};

namespace boost {
namespace mpl {

// Implementation metaclasses:

/// @brief Wrap an iterator around the front of the sequence.
template<>
struct begin_impl<dimensions_b_tag>
{
    template <typename S>
    struct apply
    {
        typedef dimensions_b_iterator<
            typename begin_impl_traversal<S, typename S::prev>::type
        > type;
    };
};

/// @brief Wrap an iterator around boost::mpl::void_.
template<>
struct end_impl<dimensions_b_tag>
{
    template <typename S>
    struct apply
    {
        typedef dimensions_b_iterator<boost::mpl::void_> type;
    };
};

/// @brief Popping from the back just means drop one array dimension.
template<>
struct pop_back_impl<dimensions_b_tag>
{
    template <typename S> struct apply;

    template <typename T, size_t N>
    struct apply< dimensions_b<T[N]> >
    {
        typedef dimensions_b<T> type;
    };
};

/// @brief Just convert the input to an integer, and add to the array dimension.
template<>
struct push_back_impl<dimensions_b_tag>
{
    template <typename S, size_t N>
    struct apply_num { };

    // We only work with dimensions_b types...
    template <typename T, size_t N>
    struct apply_num< dimensions_b<T>, N>
    {
        typedef dimensions_b<T[N]> type;
    };

    /// @brief Just convert whatever we get into a value...
    template <typename S, typename Elem>
    struct apply : apply_num<S, Elem::value> { };
};

// Metafunction specializations

/// @brief The sequence IS its identity, really.
template <typename S>
struct deref< dimensions_b_iterator<S> > : S { };

/// @brief Next is defined by the sequence.
template <typename S>
struct next< dimensions_b_iterator<S> >
{
    typedef dimensions_b_iterator<typename S::next> type;
};

/// @brief Prev is defined by the sequence.
template <typename S>
struct prior< dimensions_b_iterator<S> >
{
    typedef dimensions_b_iterator<typename S::prev> type;
};

} // namespace mpl
} // namespace boost

#endif // EXERCISE_5_7
