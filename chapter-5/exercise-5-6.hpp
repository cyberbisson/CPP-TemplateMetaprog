// ===-- chapter-5/exercise-5-6.hpp ----------------------- -*- C++ -*- --=== //
/**
 * @file
 * @brief Present array dimensions as a numerical sequence.
 *
 * <pre>
 * 5-6. Write a sequence adapter template called dimensions that, when
 *      instantiated on an array type, presents the array's dimensions as a
 *      forward, non-extensible sequence:
 *
 * typedef dimensions<char [10][5][2]> seq;
 * BOOST_STATIC_ASSERT( mpl::size<seq>::value == 3 );
 * BOOST_STATIC_ASSERT(( mpl::at_c<seq,0>::type::value == 2 ));
 * BOOST_STATIC_ASSERT(( mpl::at_c<seq,1>::type::value == 5 ));
 * BOOST_STATIC_ASSERT(( mpl::at_c<seq,2>::type::value == 10 ));
 *
 *     Consider using the type traits library facilities to simplify the
 *     implementation.
 * </pre>
 */

#ifndef EXERCISE_5_6
#define EXERCISE_5_6

#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/iterator_tags.hpp>
#include <boost/mpl/next_prior.hpp>

#include <boost/type_traits/is_array.hpp>
#include <boost/type_traits/is_same.hpp>

/// @brief A tag for tag-dispatched sequence metafunctions.
struct dimensions_tag {};

/**
 * @brief Represent the dimensions in an array type as a sequence of numbers.
 *
 * The dimensions sequence is a recursively defined sequence that strips off a
 * single array dimension as you advance through the sequence.  The recently
 * stripped dimension exists as a static member (value).
 *
 * @tparam T The (compound) array type to examine.  If T is not an array type,
 *           the sequence is not traverse-able.
 */
template <typename T>
struct dimensions : boost::mpl::void_ { };

/// @brief Basically a tuple where the "head" is the value, and the rest is
///        accessed by "tail".
template <typename T, size_t N>
struct dimensions<T[N]>
{
    static size_t const value = N;

    typedef dimensions<T[N]> type;

    /// @brief The rest of the sequence.
    typedef typename boost::mpl::if_<
        boost::is_array<T>,
        dimensions<T>,
        boost::mpl::void_
    >::type tail;

    typedef dimensions_tag tag;
};

/// @brief Define a (forward-only) iterator for our dimensions sequence.
template <typename S>
struct dimensions_iterator
{
    typedef boost::mpl::forward_iterator_tag category;
};

namespace boost {
namespace mpl {

/// @brief Just wrap the sequence in an iterator.
template <>
struct begin_impl<dimensions_tag>
{
    template <typename S>
    struct apply
    {
        typedef dimensions_iterator<S> type;
    };
};
/// @brief The end is a boost::mpl::void_ type.
template <>
struct end_impl<dimensions_tag>
{
    template <typename S>
    struct apply
    {
        typedef dimensions_iterator<boost::mpl::void_> type;
    };
};

/// @brief The iterator just contains a subset of the underlying sequence.
template <typename S>
struct deref< dimensions_iterator<S> >
{
    typedef S type;
};

/// @brief The sequence itself defines "next".
template <typename S>
struct next< dimensions_iterator<S> >
{
    typedef typename boost::mpl::if_<
        boost::is_same<boost::mpl::void_, S>,
        dimensions_iterator<boost::mpl::void_>,
        dimensions_iterator<typename S::tail> >::type type;
};

} // namespace mpl
} // namespace boost

#endif // EXERCISE_5_6
