/**
 * @file
 * @brief Insert into a binary tree.
 *
 * <pre>
 * 6-3. Write an inserter class template called binary_tree_inserter that
 *      employs the tree template from exercise 5-10 to incrementally build a
 *      binary search tree:
 *
 * typedef mpl::copy<
 *       mpl::vector_c<int,17,25,10,2,11>
 *     , binary_tree_inserter< tree<> >
 *     >::type bst;
 *
 * //       int_<17>
 * //       /      \
 * //    int_<10>  int_<25>
 * //     /    \
 * // int_<2> int_<11>
 * BOOST_STATIC_ASSERT(( mpl::equal<
 *       inorder_view<bst>
 *     , mpl::vector_c<int,2,10,11,17,25>
 *     >::value ));
 * </pre>
 *
 * @author Matt Bisson
 */

#ifndef EXERCISE_6_3
#define EXERCISE_6_3

#include "chapter-6-tree.hpp"

#include <boost/mpl/copy.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/vector_c.hpp>
using namespace boost::mpl::placeholders;

/**
 * @brief Basically indistinguishable from from any other inserter since we have
 *        a generic insert metafunction.
 *
 * Now that I've got a sensible boost::mpl::push_back_impl<tree_tag>, this
 * inserter will be easy...
 */
template <typename S, typename Op = boost::mpl::push_back<_, _> >
struct binary_tree_inserter
{
    typedef Op operation;
    typedef S state;
};

/// @brief A sorted binary tree copied from the source vector.
typedef boost::mpl::copy<
    boost::mpl::vector_c<int, 17, 25, 10, 2, 11>,
    binary_tree_inserter< tree<> >
>::type bst;

/// @brief Expected value (whitebox edition).
typedef tree<
    mpl_::integral_c<int, 17>,
    tree<
        mpl_::integral_c<int, 10>,
        mpl_::integral_c<int, 2>,
        mpl_::integral_c<int, 11> >,
    mpl_::integral_c<int, 25>
> bst_expected;
BOOST_STATIC_ASSERT((boost::is_same<bst, bst_expected>::value));

#include <boost/mpl/equal.hpp>
#include "exercise-5-10.hpp"

BOOST_STATIC_ASSERT((
    boost::mpl::equal<
        inorder_view<bst>,
        boost::mpl::vector_c<int, 2, 10, 11, 17, 25>
    >::value));

#endif // EXERCISE_6_3
