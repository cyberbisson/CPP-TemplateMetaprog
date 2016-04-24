/**
 * @file
 * @brief Augment the tree sequence API to allow addition of elements.
 *
 * @author Matt Bisson
 */

#ifndef CHAPTER_6_TREE
#define CHAPTER_6_TREE

#include "chapter-5-tree.hpp"

#include <boost/static_assert.hpp>

#include <boost/mpl/greater.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/push_back.hpp>

#include <boost/type_traits/is_same.hpp>

namespace boost {
namespace mpl {

/**
 * @brief Alter a tree structure by adding an element with sorted placement.
 *
 * This does not re-balance the tree.
 *
 * @todo "push_back" is a really crummy name for sorted tree insertion --
 *       particularly one with different "views."  USE ANOTHER NAME.
 */
template<>
struct push_back_impl<tree_tag>
{
    /// @brief The basic implementation makes a tree, assuming that the existing
    ///        sequence (S) is a leaf node.
    template <typename S, typename New>
    struct apply
        : boost::mpl::eval_if<
            boost::mpl::greater<S, New>,
            tree<S, New, void_>,
            tree<S, void_, New> >
    { };

    /// @brief Assuming that we're operating on a (sub)tree, recreate new trees
    ///        with the added element.
    template <typename New, typename Cur, typename L, typename R>
    struct apply<tree<Cur, L, R>, New>
        : boost::mpl::eval_if<
            boost::mpl::greater<Cur, New>,
            tree<
                Cur,
                typename apply<L, New>::type,
                R>,
            tree<
                Cur,
                L,
                typename apply<R, New>::type>
        >
    { };

    /// @brief Initial case.
    template <typename New>
    struct apply<tree<>, New>
    {
        typedef tree<New> type;
    };

    /// @brief An "extra" step that terminates recursion if we're simply adding
    ///        to a (sub)tree's open space.
    template <typename New>
    struct apply<void_, New>
    {
        typedef New type;
    };
};

} // namespace mpl
} // namespace boost

typedef tree<> t1;
typedef boost::mpl::push_back<t1, boost::mpl::int_<5> >::type t2;
typedef boost::mpl::push_back<t2, boost::mpl::int_<3> >::type t3;
typedef boost::mpl::push_back<t3, boost::mpl::int_<7> >::type t4;
typedef boost::mpl::push_back<t4, boost::mpl::int_<1> >::type t5;

typedef tree<
    boost::mpl::int_<5>,
    tree<boost::mpl::int_<3>, boost::mpl::int_<1>, void_>,
    boost::mpl::int_<7>
> expected_t5;
BOOST_STATIC_ASSERT((boost::is_same<t5, expected_t5>::value));

#endif // CHAPTER_6_TREE
