/**
 * @file
 * @brief Define a binary tree structure for future exercises.
 *
 * @author Matt Bisson
 */

#ifndef CHAPTER_5_10_TREE
#define CHAPTER_5_10_TREE

#include <boost/mpl/void.hpp>
using boost::mpl::void_;

/// @brief Used for Boost MPL's tag-based dispatch of sequence metafunctions.
struct tree_tag { };

/**
 * @brief A basic type to represent a binary tree.
 *
 * @tparam Cur The "current" type information for this tree node.  This may be
 *             boost::mpl::void_ to signify an empty tree.
 * @tparam L   The left branch of the tree structure.  This may be
 *             boost::mpl::void_ to indicate that the branch does not exist.
 * @tparam R   The right branch of the tree structure.  This may be
 *             boost::mpl::void_ to indicate that the branch does not exist.
 */
template <typename Cur = void_, typename L = void_, typename R = void_>
struct tree
{
    typedef tree<Cur, L, R> type;
    typedef tree_tag tag;
};

#endif // CHAPTER_5_10_TREE
