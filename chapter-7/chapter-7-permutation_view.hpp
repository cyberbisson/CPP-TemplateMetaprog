/**
 * @file
 * @brief Defines a view of a sequence that appears to alter the elements' order.
 *
 * @author Matt Bisson
 */

#ifndef CHAPTER_7_PERMUTATION_VIEW
#define CHAPTER_7_PERMUTATION_VIEW

#include <boost/mpl/advance.hpp>
#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/iterator_tags.hpp>
#include <boost/mpl/iterator_category.hpp>
#include <boost/mpl/next_prior.hpp>

/**
 * @brief Iterates across a seqence in an order defined by another sequence.
 *
 * This is an iterator adaptor that adapts any Random Access Iterator by
 * presenting the elements it traverses in an order determined by a sequence of
 * nonnegative integer indices.
 *
 * Its traversal category is determined by the category of the sequence of
 * indices.
 *
 * @tparam CurIdxIter The iterator into the index list.
 * @tparam SeqBegin   The beginning iterator for the original sequence for
 *                    access.
 */
template <typename CurIdxIter, typename SeqBegin>
struct permutation_iterator
{
    typedef CurIdxIter current_index_iter;
    typedef SeqBegin   sequence_begin;

    typedef typename boost::mpl::iterator_category<CurIdxIter>::type category;
    typedef permutation_iterator<CurIdxIter, SeqBegin> type;
};

/// @brief Type for tag-based implementation of algorithms below.
struct permutation_view_tag { };

/**
 * @brief Alter the order sequence traversal using a sequence of positions.
 *
 * <pre>
 * permutation_view<
 *     mpl::list_c<int,2,1,3,0,2>,    // indices
 *     mpl::vector_c<int,11,22,33,44> // elements
 * >
 * </pre>
 *
 * ...yields a sequence, [33,22,44,11,33]
 *
 * @tparam Indices  A sequence of indices into the "data" sequence.  The iterator
 *                  traverses this sequence and presents elements from the other
 *                  sequence.  The same index may be specified twice.  An index
 *                  outside the bounds of Sequence results in undefined behavior.
 * @tparam Sequence The data sequence to present when iterators are dereferenced.
 */
template <typename Indices, typename Sequence>
struct permutation_view
{
    typedef Indices  indices;
    typedef Sequence orig_sequence;

    typedef permutation_view_tag tag;
};

namespace boost {
namespace mpl {

/// @brief Load an iterator with the beginning to both sequences.
template <>
struct begin_impl<permutation_view_tag>
{
    // Maybe I should just use duck typing instead of disallowing anything but
    // permutation_view (i.e., use Sequence::indices, etc.)
    template <typename Sequence> struct apply { };

    template <typename Indices, typename Sequence>
    struct apply< permutation_view<Indices, Sequence> >
        : permutation_iterator<
            typename begin<Indices>::type, typename begin<Sequence>::type>
    { };
};

/// @brief An iterator with the end of the indices sequence and the beginning of
///        the other.
template <>
struct end_impl<permutation_view_tag>
{
    // Maybe I should only really allow permutation_view here...
    template <typename Sequence>
    struct apply
        : permutation_iterator<
            typename end<typename Sequence::indices>::type,
            typename begin<typename Sequence::orig_sequence>::type>
    { };
};

/// @brief Advance the prescribed amount, and return the element found.
template <typename CurIdxIter, typename SeqBegin>
struct deref< permutation_iterator<CurIdxIter, SeqBegin> >
    : deref<typename advance<SeqBegin, typename deref<CurIdxIter>::type>::type>
{ };

/// @brief Advance only the index iterator.
template <typename CurIdxIter, typename SeqBegin>
struct next< permutation_iterator<CurIdxIter, SeqBegin> >
    : permutation_iterator<typename next<CurIdxIter>::type, SeqBegin>
{ };

/// @brief Move only the index iterator.
template <typename CurIdxIter, typename SeqBegin>
struct prior< permutation_iterator<CurIdxIter, SeqBegin> >
    : permutation_iterator<typename prior<CurIdxIter>::type, SeqBegin>
{ };

} // namespace mpl
} // namespace boost

#endif // CHAPTER_7_PERMUTATION_VIEW
