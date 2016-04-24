/**
 * @file
 * @brief Write a tree structure with different view-based traversals.
 *
 * <pre>
 * 5-10* Write a tree class template for composing compile-time binary tree
 *       data structures:
 *
 *           typedef tree<                  //     double
 *                 double                   //     /   \
 *               , tree<void*,int,long>     //   void* char
 *               , char                     //   /  \
 *               > tree_seq;                // int  long
 *
 *       Implement iterators for pre-order, in-order, and post-order traversal
 *       of the tree elements:
 *
 *           BOOST_STATIC_ASSERT(( mpl::equal<
 *                 preorder_view<tree_seq>
 *               , mpl::vector<double,void*,int,long,char>
 *               , boost::is_same<_1,_2>
 *               >::value ));
 *
 *           BOOST_STATIC_ASSERT(( mpl::equal<
 *                 inorder_view<tree_seq>
 *               , mpl::vector<int,void*,long,double,char>
 *               , boost::is_same<_1,_2>
 *               >::value ));
 *
 *           BOOST_STATIC_ASSERT(( mpl::equal<
 *                 postorder_view<tree_seq>
 *               , mpl::vector<int,long,void*,char,double>
 *               , boost::is_same<_1,_2>
 *               >::value ));
 * </pre>
 *
 * @todo Pre-order tree traversal!
 * @todo Post-order tree traversal!
 * @author Matt Bisson
 */

#ifndef EXERCISE_5_10
#define EXERCISE_5_10

#include "chapter-5-tree.hpp"

#include <boost/static_assert.hpp>

#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/greater.hpp>
#include <boost/mpl/iterator_tags.hpp>
#include <boost/mpl/next_prior.hpp>

#include <boost/type_traits/is_same.hpp>


/// @brief A tag for tag-dispatched sequence metafunctions.
struct inorder_view_tag { };

/**
 * @brief Compels iterators to traverse the tree "in order".
 *
 * @tparam T The binary tree to traverse.
 */
template <typename T>
struct inorder_view
{
    typedef T tree_root;
    typedef inorder_view_tag tag;
    typedef boost::mpl::forward_iterator_tag category;
};

/**
 * @brief Establish an iterator to contain in-order traversal of the binary tree.
 *
 * @tparam Cur        The current (sub)tree.
 * @tparam Parent     This is an iterator to the parent of this (sub)tree, or
 *     "void_".
 * @tparam VisitCount This is a marker to indicate next steps during tree
 *     traversal.  In an in-order tree traversal, a visit count of 0 indicates
 *     "descent left", 1 indicates "return myself," and 2 indicates "descent
 *     right."
 */
template <typename Cur, typename Parent, int VisitCount>
struct inorder_view_iterator
{
    typedef Cur current_tree;
    typedef Parent parent_iterator;
    static int const visit_count = VisitCount;

    typedef inorder_view_iterator<Cur, Parent, VisitCount> type;
};

/// @brief Establish an end to the sequence.
typedef inorder_view_iterator<void_, void_, 0> inorder_view_iterator_end;

namespace boost {
namespace mpl {

/**
 * @brief Simply returns inorder_view_iterator_end.
 *
 * @note Define end_impl before begin_impl, as the latter uses the former in an
 *       empty tree.
 */
template<>
struct end_impl<inorder_view_tag>
{
    template <typename S>
    struct apply : inorder_view_iterator_end { };
};

/// @brief The begin algorithm needs to traverse to the leftmost element,
///        creating iterators along the way.
template<>
struct begin_impl<inorder_view_tag>
{
    /// @brief For the leaf, we've reached the beginning.  Set visit count to 1.
    template <typename Self, typename Parent>
    struct apply_on_iterator : inorder_view_iterator<Self, Parent, 1> { };

    /// @brief For every subtree, set the visit count to 1.
    template <typename Cur, typename L, typename R, typename Parent>
    struct apply_on_iterator<tree<Cur, L, R>, Parent>
        : apply_on_iterator<
            L,
            inorder_view_iterator<tree<Cur, L, R>, Parent, 1>
        > { };

    /// @brief With an empty tree, begin == end.
    template <typename Parent>
    struct apply_on_iterator< tree<>, Parent >
        : boost::mpl::end< inorder_view< tree<> > > { };

    /// @brief Start here.  The root's parent is also the end of the sequence.
    template <typename S>
    struct apply
        : apply_on_iterator<
            typename S::tree_root,
            inorder_view_iterator_end
        > { };
};

/**
 * @brief In-order traversal.
 *
 * Esentially, we're going to move about the tree, keeping track of how many
 * visits to each element (using the iterator's VisitCount parameter).  Based on
 * this value, the next algorithm has different behavior.
 *
 * This less-specialized metafunction must be a leaf (trees should all be
 * covered in specializations).  Return the parent.  If the parent is "end",
 * we've fully traversed the tree.
 */
template <typename Cur, typename Parent, int VisitCount>
struct next< inorder_view_iterator<Cur, Parent, VisitCount> >
    : boost::mpl::eval_if<
        boost::is_same<inorder_view_iterator_end, Parent>,
        inorder_view_iterator_end,
        next<
            inorder_view_iterator<
                typename Parent::current_tree,
                typename Parent::parent_iterator,
                Parent::visit_count>
            >
        > { };
/// @brief Visiting a leaf for the first time: present it as the "next" item.
template <typename Cur, typename Parent>
struct next< inorder_view_iterator<Cur, Parent, 0> >
    : inorder_view_iterator<Cur, Parent, 1> { };

/// @brief This is an error -- Visit count must not be [0,3].
template <typename Cur, typename L, typename R, typename Parent, int VisitCount>
struct next< inorder_view_iterator<tree<Cur, L, R>, Parent, VisitCount> > { };

/// @brief We've never visited this item, so we should start by going left.
template <typename Cur, typename L, typename R, typename Parent>
struct next< inorder_view_iterator<tree<Cur, L, R>, Parent, 0> >
    : next<
        inorder_view_iterator<
            L,
            inorder_view_iterator<tree<Cur, L, R>, Parent, 1>,
            0
        >
    > { };
/// @brief Same as above, but L node is empty, so go back up...
template <typename Cur, typename R, typename Parent>
struct next< inorder_view_iterator<tree<Cur, void_, R>, Parent, 0> >
    : next< inorder_view_iterator<tree<Cur, void_, R>, Parent, 1> > { };
/// @brief Seen this node once, so we should present it as the "next" item.
template <typename Cur, typename L, typename R, typename Parent>
struct next< inorder_view_iterator<tree<Cur, L, R>, Parent, 1> >
    : inorder_view_iterator<tree<Cur, L, R>, Parent, 2> { };
/// @brief Visited this node twice already, so the only place to go is right.
template <typename Cur, typename L, typename R, typename Parent>
struct next< inorder_view_iterator<tree<Cur, L, R>, Parent, 2> >
    : next<
        inorder_view_iterator<
            R,
            inorder_view_iterator<tree<Cur, L, R>, Parent, 3>,
            0
        >
    > { };
/// @brief Same as above, but R node is empty, so go back up...
template <typename Cur, typename L, typename Parent>
struct next< inorder_view_iterator<tree<Cur, L, void_>, Parent, 2> >
    : next< inorder_view_iterator<tree<Cur, L, void_>, Parent, 3> > { };
/// @brief Go back up the tree.  If we reach "end" as the parent, we've fully
///        traversed the tree.
template <typename Cur, typename L, typename R, typename Parent>
struct next< inorder_view_iterator<tree<Cur, L, R>, Parent, 3> >
    : boost::mpl::eval_if<
        boost::is_same<inorder_view_iterator_end, Parent>,
        inorder_view_iterator_end,
        next<
            inorder_view_iterator<
                typename Parent::current_tree,
                typename Parent::parent_iterator,
                Parent::visit_count>
            >
        > { };

/// @brief This specialization is only for leaf nodes.  Grab it directly from
///        the iterator.
template <typename Cur, typename Parent, int VisitCount>
struct deref< inorder_view_iterator<Cur, Parent, VisitCount> >
{
    typedef Cur type;
};

/// @brief Grab the first value from the subtree contained in the iterator.
template <typename Cur, typename L, typename R, typename Parent, int VisitCount>
struct deref< inorder_view_iterator<tree<Cur, L, R>, Parent, VisitCount> >
{
    typedef Cur type;
};

} // namespace mpl
} // namespace boost

#if 0

template <typename T>
struct preorder_view
{

};

template <typename T>
struct postorder_view
{

};

#endif

/**
 * @brief A test tree.
 *
 * <pre>
 *     double
 *     /   \
 *   void* char
 *   /  \
 * int  long
 * </pre>
 */
typedef tree<
    double,
    tree<void*, int, long>,
    char
> tree_seq;

/**
 * @brief A more involved test tree.
 *
 * <pre>
 *         double
 *       /       \
 *   short        int
 *   /   \       /   \
 * long float  void_ char
 *       /
 *     void*
 * </pre>
 */
typedef tree<
    double,
    tree<
        short,
        long,
        tree<float, void*>
        >,
    tree<
        int,
        void_,
        char>
    > tree_seq_hard;

#ifdef PARANOID_DEBUG_TEST
typedef boost::mpl::begin< inorder_view<tree_seq_hard> >::type tmp1;
typedef boost::mpl::deref<tmp1>::type tmp1d;
BOOST_STATIC_ASSERT((boost::is_same<long, tmp1d>::value));

typedef boost::mpl::next<tmp1>::type tmp2;
typedef boost::mpl::deref<tmp2>::type tmp2d;
BOOST_STATIC_ASSERT((boost::is_same<short, tmp2d>::value));

typedef boost::mpl::next<tmp2>::type tmp3;
typedef boost::mpl::deref<tmp3>::type tmp3d;
BOOST_STATIC_ASSERT((boost::is_same<void*, tmp3d>::value));

typedef boost::mpl::next<tmp3>::type tmp4;
typedef boost::mpl::deref<tmp4>::type tmp4d;
BOOST_STATIC_ASSERT((boost::is_same<float, tmp4d>::value));

typedef boost::mpl::next<tmp4>::type tmp5;
typedef boost::mpl::deref<tmp5>::type tmp5d;
BOOST_STATIC_ASSERT((boost::is_same<double, tmp5d>::value));

typedef boost::mpl::next<tmp5>::type tmp6;
typedef boost::mpl::deref<tmp6>::type tmp6d;
BOOST_STATIC_ASSERT((boost::is_same<int, tmp6d>::value));

typedef boost::mpl::next<tmp6>::type tmp7;
typedef boost::mpl::deref<tmp7>::type tmp7d;
BOOST_STATIC_ASSERT((boost::is_same<char, tmp7d>::value));

typedef boost::mpl::next<tmp7>::type tmp8;
typedef boost::mpl::end< inorder_view<tree_seq_hard> >::type tmp_end;
BOOST_STATIC_ASSERT((boost::is_same<tmp_end, tmp8>::value));
#endif // PARANOID_DEBUG_TEST

#include <boost/mpl/vector.hpp>
using namespace boost::mpl::placeholders;

BOOST_STATIC_ASSERT((
    boost::mpl::equal<
        inorder_view<tree_seq>,
        boost::mpl::vector<int, void*, long, double, char>,
        boost::is_same<_1, _2>
    >::value));

BOOST_STATIC_ASSERT((
    boost::mpl::equal<
        inorder_view<tree_seq_hard>,
        boost::mpl::vector<long, short, void*, float, double, int, char>,
        boost::is_same<_1, _2>
    >::value));

#endif // EXERCISE_5_10
