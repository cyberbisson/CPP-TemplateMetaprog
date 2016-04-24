/**
 * @file
 * @brief Create a reverse view and iterator.
 *
 * <pre>
 * 7-7. Design and implement a reverse iterator adaptor with semantics analogous
 *      to those of std::reverse_iterator.  Make its category the same as the
 *      category of the underlying iterator.  Use the resulting iterator to
 *      implement a reverse_view template.
 * </pre>
 *
 * @author Matt Bisson
 */

#ifndef EXERCISE_7_7
#define EXERCISE_7_7

#include <boost/static_assert.hpp>

#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/iterator_category.hpp>
#include <boost/mpl/iterator_tags.hpp>
#include <boost/mpl/next_prior.hpp>
#include <boost/mpl/or.hpp>

#include <boost/type_traits/is_same.hpp>

/**
 * @brief Wraps any iterator with the intent of reversing the direction of next
 *        and prior.
 */
template <typename ForwardIt>
struct reverse_iterator
{
    typedef ForwardIt base;
    typedef typename boost::mpl::iterator_category<ForwardIt>::type category;

    typedef reverse_iterator<ForwardIt> type;
};

/**
 * @brief Determines if the source iterator is suitable for reversal.
 *
 * @tparam Iterator Some "normal" iterator acquired with boost::mpl::begin, or
 *                  some other ordinary means.
 */
template <typename Iterator>
struct is_valid_reverse_category
    : boost::mpl::or_<
        boost::is_same<
            typename boost::mpl::iterator_category<Iterator>::type,
            boost::mpl::bidirectional_iterator_tag>,
        boost::is_same<
            typename boost::mpl::iterator_category<Iterator>::type,
            boost::mpl::random_access_iterator_tag>
    >
{ };

namespace boost {
namespace mpl {

/// @brief Acquire a reverse_iterator at the end of a sequence.
template <typename Sequence>
struct rend
{
    typedef typename prior<typename begin<Sequence>::type>::type end_iterator;
    BOOST_STATIC_ASSERT((is_valid_reverse_category<end_iterator>::value));

    typedef ::reverse_iterator<end_iterator> type;
};

/// @brief Grab a reverse_iterator from the a sequence directly.
template <typename Sequence>
struct rbegin
{
    typedef typename prior<typename end<Sequence>::type>::type first_iterator;
    BOOST_STATIC_ASSERT((is_valid_reverse_category<first_iterator>::value));

    typedef ::reverse_iterator<first_iterator> type;
};

/// @brief Undo double-indirection of the reverse_iterator.
template <typename ForwardIt>
struct deref< ::reverse_iterator<ForwardIt> > : deref<ForwardIt> { };

/// @brief Turn next into prior.
template <typename ForwardIt>
struct next< ::reverse_iterator<ForwardIt> >
    : ::reverse_iterator<typename prior<ForwardIt>::type> { };

/// @brief Turn prior into next.
template <typename ForwardIt>
struct prior< ::reverse_iterator<ForwardIt> >
    : ::reverse_iterator<typename next<ForwardIt>::type> { };

} // namespace mpl
} // namespace boost

#include <boost/mpl/vector_c.hpp>

/// @brief Tests functionality from Exercise 7-7
namespace ex_7_7ns {

typedef boost::mpl::vector_c<int, 1, 2> v1;
typedef boost::mpl::rbegin<v1>::type ri0;
typedef boost::mpl::deref<ri0>::type rv0;
BOOST_STATIC_ASSERT((rv0::value == 2));

typedef boost::mpl::next<ri0>::type ri1;
typedef boost::mpl::deref<ri1>::type rv1;
BOOST_STATIC_ASSERT((rv1::value == 1));

typedef boost::mpl::next<ri1>::type ri2;
typedef boost::mpl::rend<v1>::type ri_end;
BOOST_STATIC_ASSERT((boost::is_same<ri2, ri_end>::value));

typedef boost::mpl::prior<ri1>::type ri1_prior;
BOOST_STATIC_ASSERT((boost::is_same<ri1_prior, ri0>::value));

} // namespace ex_7_7ns

#endif // EXERCISE_7_7
