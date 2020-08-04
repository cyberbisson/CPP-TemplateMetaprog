// ===-- chapter-7/chapter-7-zip_view.hpp ----------------- -*- C++ -*- --=== //
/**
 * @file
 * @brief "Zip" corresponding elements of N arrays into a sequence of N-length
 *        subsequences.
 *
 * @author Matt Bisson
 */

#ifndef CHAPTER_7_ZIP_VIEW
#define CHAPTER_7_ZIP_VIEW

#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/iterator_category.hpp>
#include <boost/mpl/iterator_range.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/transform.hpp>
using namespace boost::mpl::placeholders;

// This is work from exercise 7-2...
#ifndef FORWARD_ONLY_ZIP_VIEW

#include <boost/mpl/empty.hpp>
#include <boost/mpl/find_if.hpp>
#include <boost/mpl/filter_view.hpp>

#include <boost/type_traits/is_same.hpp>

/**
 * @brief A simple metafunction to get the iterator category from the first
 *        iterator in a sequence.
 *
 * The iterator category must not change throughout the entire sequence.
 *
 * @tparam S A sequence in the sequence of sequences.
 */
template <typename S>
struct extract_iterator_category
{
    typedef typename boost::mpl::begin<S>::type::category type;
};

/**
 * @brief Assuming a sequence of sequences, find the least refined category of
 *        all subsequences.
 *
 * Basically, if we have nothing but random access, return that.  If we have
 * nothing but random access or bidirectional, return bidirectional, and if
 * we have anything else, just return forward_iterator_tag.
 *
 * In the case that we have random_access iterators, this should be pretty
 * stingy with its template instantiations.  If there are nothing but
 * forward_iterator types, though, this will probably be a bit worse than a
 * more eager approach.
 *
 * @tparam S The sequence of sequences.
 */
template <typename S>
struct least_refined_iterator_category
{
    /// @brief Show us everything that is not categorized as "random access."
    typedef typename boost::mpl::filter_view<
        S,
        boost::mpl::not_<
            boost::is_same<
                extract_iterator_category<_1>,
                boost::mpl::random_access_iterator_tag>
        >
    >::type non_random_access_iterators;

    /// @brief Show us everything that is not categorized as either
    ///        "bidirectional" OR "random access."
    typedef typename boost::mpl::filter_view<
        non_random_access_iterators,
        boost::mpl::not_<
            boost::is_same<
                extract_iterator_category<_1>,
                boost::mpl::bidirectional_iterator_tag>
        >
    >::type non_bidirectional_iterators;

    typedef typename boost::mpl::if_<
        boost::mpl::empty<non_random_access_iterators>,
        boost::mpl::random_access_iterator_tag,
        typename boost::mpl::if_<
            boost::mpl::empty<non_bidirectional_iterators>,
            boost::mpl::bidirectional_iterator_tag,
            boost::mpl::forward_iterator_tag>::type
        >::type type;
};

#else

// This is a place-holder until exercise 7-2
template <typename S>
struct least_refined_iterator_category
{
    typedef boost::mpl::forward_iterator_tag type;
};

#endif // !FORWARD_ONLY_ZIP_VIEW

/// @brief An iterator into a sequence of sequences.
template <typename IteratorSeq, typename Category>
struct zip_iterator
    : boost::mpl::transform< IteratorSeq, boost::mpl::deref<_1> >
{
    typedef IteratorSeq base;
    typedef Category category;
};

/// @brief Type for tag-based implementation of algorithms below.
struct zip_view_tag { };

/**
 * @brief Wraps corresponding elements across a sequence of sequences.
 *
 * @tparam Sequences A sequence of identically sized sequences.
 */
template <typename Sequences>
struct zip_view
    : boost::mpl::iterator_range<
        zip_iterator<
            typename boost::mpl::transform<
                Sequences, boost::mpl::begin<_1>
            >::type,
            typename least_refined_iterator_category<Sequences>::type
        >,
        zip_iterator<
            typename boost::mpl::transform<
                Sequences, boost::mpl::end<_1>
            >::type,
            typename least_refined_iterator_category<Sequences>::type
        >
    >
{
    typedef zip_view_tag tag;
};

#include <boost/static_assert.hpp>
#include <boost/mpl/or.hpp>

#include <boost/mpl/at.hpp>

namespace boost {
namespace mpl {

/// @brief Creates a sequence of the next element for each (sub-)iterator.
template <typename IteratorSeq, typename Category>
struct next< ::zip_iterator<IteratorSeq, Category> >
{
    typedef ::zip_iterator<
        typename transform< IteratorSeq, next<_1> >::type,
        Category
    > type;
};

// Begin metafunctions for exercise 7-2...

/**
 * @brief Creates a sequence from the result of boost::mpl::advance.
 *
 * I'm only allowing this metafunction for random_access_iterator_tag at the
 * moment...
 */
template <typename IteratorSeq, typename N>
struct advance< ::zip_iterator<IteratorSeq, random_access_iterator_tag>, N >
{
    typedef ::zip_iterator<
        typename transform< IteratorSeq, advance<_1, N> >::type,
        random_access_iterator_tag
    > type;
};

/**
 * @brief Create a sequence from the result of boost::mpl::at.
 *
 * Only define behavior for random_access_iterator_tag.  Others can be done,
 * but we'll leave that for later.
 */
template <>
struct at_impl<zip_view_tag>
{
    template <typename S, typename Category, typename N> struct apply_impl { };

    template <typename S, typename N>
    struct apply_impl<S, random_access_iterator_tag, N>
    {
        typedef ::zip_iterator<
            typename transform< S, at<_1, N> >::type,
            random_access_iterator_tag> type;
    };

    template <typename S, typename N> struct apply { };
    template <typename S, typename N>
    struct apply< ::zip_view<S>, N >
        : apply_impl<
            S,
            typename least_refined_iterator_category<S>::type,
            N>
    { };
};

/// @brief Specialize prior, but only for bidirection or better iterator types.
template <typename IteratorSeq, typename Category>
struct prior< ::zip_iterator<IteratorSeq, Category> >
{
    BOOST_STATIC_ASSERT((
        boost::mpl::or_<
            boost::is_same<
                Category,
                boost::mpl::bidirectional_iterator_tag>,
            boost::is_same<
                Category,
                boost::mpl::random_access_iterator_tag>
        >::type::value));

    typedef ::zip_iterator<
        typename transform< IteratorSeq, prior<_1> >::type,
        Category
    > type;
};

} // namespace mpl
} // namespace boost

#endif // CHAPTER_7_ZIP_VIEW
