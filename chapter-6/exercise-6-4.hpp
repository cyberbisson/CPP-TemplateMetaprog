// ===-- chapter-6/exercise-6-4.hpp ----------------------- -*- C++ -*- --=== //
/**
 * @file
 * @brief Search a binary tree structure using an inserter.
 *
 * <pre>
 * 6-4. Write an algorithm metafunction called binary_tree_search that performs
 *      binary search on trees built using binary_tree_inserter from exercise
 *      6-3.
 *
 * typedef binary_tree_search<bst,int_<11> >::type pos1;
 * typedef binary_tree_search<bst,int_<20> >::type pos2;
 * typedef mpl::end<bst>::type                     end_pos;
 *
 * BOOST_STATIC_ASSERT((!boost::is_same< pos1,end_pos >::value));
 * BOOST_STATIC_ASSERT((boost::is_same< pos2,end_pos >::value));
 * </pre>
 *
 * @author Matt Bisson
 */

#ifndef EXERCISE_6_4
#define EXERCISE_6_4

#include "chapter-5-tree.hpp"

#include <boost/mpl/end.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/greater.hpp>
#include <boost/mpl/if.hpp>


/// @brief Quick and dirty (non-iterator, I know) way to mark the end of the
///        tree sequence...
struct tree_end
{
    typedef tree_end type;
};

namespace boost {
namespace mpl {

/// @brief Pass along our special "end" type.
template<>
struct end_impl<tree_tag>
{
    template <typename S> struct apply : tree_end { };
};

} // namespace mpl
} // namespace boost

/**
 * @brief Perform a search on a binary tree structure.
 *
 * If this algorithm finds nothing matching Elem, it returns
 * boost::mpl::end< tree<> >.
 *
 * @tparam S    A (sub)tree to search.
 * @tparam Elem The element to search for.
 *
 * @note The unspecialized version of this metafunction deals only with leaf
 *       nodes in the tree.
 */
template <typename S, typename Elem>
struct binary_tree_search
    : boost::mpl::eval_if<
        boost::mpl::equal_to<Elem, S>,
        S,
        boost::mpl::end< tree<> >
    > { };

/// @brief If we get an empty subtree, indicate that there is nothing found.
template <typename Elem>
struct binary_tree_search<boost::mpl::void_, Elem>
    : boost::mpl::end< tree<> > { };

/// @brief The usual binary tree logic.
template <typename Cur, typename L, typename R, typename Elem>
struct binary_tree_search<tree<Cur, L, R>, Elem>
    : boost::mpl::eval_if<
        boost::mpl::equal_to<Elem, Cur>,
        tree<Cur, L, R>,
        boost::mpl::eval_if<
            boost::mpl::greater<Elem, Cur>,
            binary_tree_search<R, Elem>,
            binary_tree_search<L, Elem> >
    > { };

#include <boost/mpl/copy.hpp>
#include <boost/mpl/vector_c.hpp>
#include <boost/type_traits/is_same.hpp>

/// @brief Tests functionality from Exercise 6-4.
namespace ex_6_4ns {

typedef boost::mpl::copy<
    boost::mpl::vector_c<int, 17, 25, 10, 2, 11>,
    binary_tree_inserter< tree<> >
>::type bst;
typedef binary_tree_search< bst, boost::mpl::int_<20> > qq;
typedef binary_tree_search< bst, boost::mpl::int_<11> >::type pos1;
typedef binary_tree_search< bst, boost::mpl::int_<20> >::type pos2;
typedef boost::mpl::end<bst>::type                            end_pos;

// Note: equal means int_<11> == int_<20> by some miracle -- equal_to is correct.
BOOST_STATIC_ASSERT((
   !boost::mpl::equal_to<
       boost::mpl::int_<11>,
       boost::mpl::int_<20>
   >::value));

BOOST_STATIC_ASSERT((!boost::is_same<pos1, end_pos>::value));
BOOST_STATIC_ASSERT(( boost::is_same<pos2, end_pos>::value));

} // namespace ex_6_4ns

#endif // EXERCISE_6_4
