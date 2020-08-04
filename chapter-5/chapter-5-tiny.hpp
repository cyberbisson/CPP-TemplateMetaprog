// ===-- chapter-5/chapter-5-tiny.hpp --------------------- -*- C++ -*- --=== //
/**
 * @file
 * @brief Define a "tiny" sequence with modifications from examples in Chapter
 *        5.
 *
 * @author Matt Bisson
 */

#ifndef CHAPTER_5_TINY
#define CHAPTER_5_TINY

#include <boost/static_assert.hpp>

#include <boost/mpl/at.hpp>
#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/clear.hpp>
#include <boost/mpl/insert.hpp>
#include <boost/mpl/iterator_tags.hpp>
#include <boost/mpl/minus.hpp>
#include <boost/mpl/next_prior.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/pop_back.hpp>
#include <boost/mpl/pop_front.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/mpl/push_front.hpp>
#include <boost/mpl/size.hpp>

#include <boost/type_traits/is_same.hpp>

/// @brief Quickly define a NULL type
struct none { };

/// @brief Type for tag-based implementation of algorithms below.
struct tiny_tag {};

/**
 * @brief Define an iterator for use with the tiny sequence type.
 *
 * @tparam Tiny The sequence to iterate over.
 * @tparam Pos  The current location in the sequence.
 */
template <typename Tiny, typename Pos>
struct tiny_iterator
{
    /// @brief The tiny sequence has Random Access iteration semantics.
    typedef boost::mpl::random_access_iterator_tag category;
};

/**
 * @brief A small, random-access sequence type.
 * @tparam T0..T2 Types contained within the sequence.
 */
template <typename T0 = none, typename T1 = none, typename T2 = none>
struct tiny
{
    typedef tiny_tag tag;
    typedef tiny type;
    typedef T0 t0;
    typedef T1 t1;
    typedef T2 t2;
};

/// @brief Provide O(1) access to sequences tagged with tiny_tag
template <typename Tiny, int Pos> struct tiny_at { };

template <typename Tiny>
struct tiny_at<Tiny, 0>
{
    typedef typename Tiny::t0 type;
};
template <typename Tiny>
struct tiny_at<Tiny, 1>
{
    typedef typename Tiny::t1 type;
};
template <typename Tiny>
struct tiny_at<Tiny, 2>
{
    typedef typename Tiny::t2 type;
};

// Indirection to improve back insertion:

/**
 * @brief Add an element to the end of the tiny sequence.
 *
 * @tparam Tiny The sequence to augment.
 * @tparam T    The new element to add.
 * @tparam N    The current size of Tiny.
 */
template <typename Tiny, typename T, int N>
struct tiny_push_back;

template <typename Tiny, typename T>
struct tiny_push_back<Tiny, T, 0> : tiny<T, none, none> { };
template <typename Tiny, typename T>
struct tiny_push_back<Tiny, T, 1> : tiny<typename Tiny::t0, T, none> { };
template <typename Tiny, typename T>
struct tiny_push_back<Tiny, T, 2>
    : tiny<typename Tiny::t0, typename Tiny::t1, T> { };

#ifndef PRE_EXERCISE_5_3
/**
 * @brief Insert into the tiny sequence.
 *
 * If the sequence is full, this will not drop elements, it will fail an
 * assertion and abort compilation.
 *
 * @tparam Tiny The sequence to augment.
 * @tparam T    The new element to add.
 * @tparam N    The current size of Tiny.
 */
template <typename Tiny, typename T, int N>
struct tiny_insert;

template <typename Tiny, typename T>
struct tiny_insert<Tiny, T, 0>
    : tiny<T, typename Tiny::t0, typename Tiny::t1>
{ BOOST_STATIC_ASSERT((boost::is_same<typename Tiny::t2, none>::value)); };
template <typename Tiny, typename T>
struct tiny_insert<Tiny, T, 1>
    : tiny<typename Tiny::t0, T, typename Tiny::t1>
{ BOOST_STATIC_ASSERT((boost::is_same<typename Tiny::t2, none>::value)); };
template <typename Tiny, typename T>
struct tiny_insert<Tiny, T, 2>
    : tiny<typename Tiny::t0, typename Tiny::t1, T>
{ BOOST_STATIC_ASSERT((boost::is_same<typename Tiny::t2, none>::value)); };
#endif

/// @brief Used to improve end metafunction performance, etc.
template <typename T0, typename T1, typename T2>
struct tiny_size : boost::mpl::int_<3> { };

template <typename T0, typename T1>
struct tiny_size<T0, T1, none> : boost::mpl::int_<2> { };
template <typename T0>
struct tiny_size<T0, none, none> : boost::mpl::int_<1> { };
template <>
struct tiny_size<none, none, none> : boost::mpl::int_<0> { };

namespace boost {
namespace mpl {

// Implement the required operations

/// @brief Iterator next simply increments our numerical position info.
template <typename Tiny, typename Pos>
struct next< tiny_iterator<Tiny,Pos> >
{
    typedef tiny_iterator<
        Tiny,
        typename boost::mpl::next<Pos>::type
        > type;
};

/// @brief Iterator prior simply decrements our numerical position info.
template <typename Tiny, typename Pos>
struct prior< tiny_iterator<Tiny,Pos> >
{
    typedef tiny_iterator<
        Tiny,
        typename boost::mpl::prior<Pos>::type
        > type;
};

/// @brief Iterator advance is simple numerical addition.
template <typename Tiny, typename Pos, typename N>
struct advance< tiny_iterator<Tiny,Pos>, N >
{
    typedef tiny_iterator<
        Tiny,
        typename boost::mpl::plus<Pos,N>::type
        > type;
};

/// @brief Dereferencing the iterator is the first time we actually examine
///        tiny.
template <typename Tiny, typename Pos>
struct deref< tiny_iterator<Tiny,Pos> > : at<Tiny,Pos> { };

/// @brief Our iterators deal in integers, so simply subtract the two.
template <typename Tiny, typename Pos1, typename Pos2>
struct distance<
    tiny_iterator<Tiny,Pos1>,
    tiny_iterator<Tiny,Pos2> >
    : boost::mpl::minus<Pos2, Pos1> { };

/// @brief Forward to tiny_at for O(1) access
template <>
struct at_impl<tiny_tag>
{
    template <typename Tiny, typename N>
    struct apply : tiny_at<Tiny, N::value> { };
};

/// @brief Initialize the iterator with a position of 0.
template <>
struct begin_impl<tiny_tag>
{
    template <typename Tiny>
    struct apply
    {
        typedef tiny_iterator< Tiny, int_<0> > type;
    };
};

/// @brief Finding the end requires tiny_size, which is O(1) complexity.
template <>
struct end_impl<tiny_tag>
{
    template <typename Tiny>
    struct apply
    {
        typedef tiny_iterator<
            Tiny,
            typename tiny_size<
                typename Tiny::t0,
                typename Tiny::t1,
                typename Tiny::t2
                >::type
            > type;
    };
};

/// @brief Forward the MPL size lambda over to tiny_size.
template <>
struct size_impl<tiny_tag>
{
    template <typename Tiny>
    struct apply
        : tiny_size<
            typename Tiny::t0,
            typename Tiny::t1,
            typename Tiny::t2
        > { };
};

// Extensibility

/// @brief Simply return a new, empty tiny sequence.
template <>
struct clear_impl<tiny_tag>
{
    template <typename Tiny>
    struct apply : tiny<> { };
};

/// @brief If we can insert, use that, otherwise, use tiny_push_back.
template <>
struct push_back_impl<tiny_tag>
{
    // tiny_push_back and tiny_insert are the same complexity.
    template <typename Tiny, typename T>
#ifdef PRE_EXERCISE_5_3
    struct apply
        : tiny_push_back<Tiny, T, size<Tiny>::value> { };
#else
    struct apply
        : tiny_insert<Tiny, T, size<Tiny>::value> { };
#endif
};

/**
 * @file
 *
 * Additional exercises:
 *
 * <pre>
 * 5-2. Note that push_back won't compile if its tiny argument already has three
 *      elements. How can we get the same guarantees for push_front?
 * </pre>
 */
// (Changed) A simple assert that either t2 = none, or size<Tiny> < 3

/// @brief Front insertion is straightforward.  Assert we're not already full.
template <>
struct push_front_impl<tiny_tag>
{
    template <typename Tiny, typename T>
    struct apply : tiny<T, typename Tiny::t0, typename Tiny::t1>
    {
        // See exercise 5-2
        BOOST_STATIC_ASSERT((boost::is_same<typename Tiny::t2, none>::value));
    };
};

} // namespace mpl
} // namespace boost

/**
 * @file
 *
 * <pre>
 * 5-3. Drawing on the example of our push_back implementation, implement insert
 *      for tiny sequences.  Refactor the implementation of push_back so that it
 *      shares more code with insert.
 * </pre>
 */

// Created tiny_insert, modified push_back (above)

namespace boost {
namespace mpl {

/// @brief Using tiny_insert is O(1) time.
template <>
struct insert_impl<tiny_tag>
{
    template <typename Tiny, typename Pos, typename T>
    struct apply;

    template <typename Tiny, typename Pos, typename T>
    struct apply<Tiny, tiny_iterator<Tiny,Pos>, T>
        : tiny_insert<Tiny, T, Pos::value> { };
};

} // namespace mpl
} // namespace boost

/**
 * @file
 *
 * <pre>
 * 5-4. How could we reduce the number of template instantiations required by
 *      our implementation of push_back? (Hint: Look at our implementation of
 *      end in section 5.11.5 again.) How does that interact with the
 *      refactoring in the previous exercise?
 * </pre>
 */

/**
 * @file
 *
 * <pre>
 * 5-5. Implement the pop_front, pop_back, and erase algorithms for tiny.
 * </pre>
 */
#include <boost/mpl/erase.hpp>

/**
 * @brief Erase a range of elements from a tiny sequence.
 *
 * @tparam S     The sequence to alter.
 * @tparam First The first (inclusive) element to remove.
 * @tparam Last  The last (inclusive) element to remove.
 */
template <typename S, int First, int Last>
struct tiny_erase { };

template <typename S>
struct tiny_erase<S,0,1> : tiny<typename S::t1, typename S::t2> { };
template <typename S>
struct tiny_erase<S,0,2> : tiny<typename S::t2> { };
template <typename S>
struct tiny_erase<S,0,3> : tiny<> { };
template <typename S>
struct tiny_erase<S,1,2> : tiny<typename S::t0, typename S::t2> { };
template <typename S>
struct tiny_erase<S,1,3> : tiny<typename S::t0> { };
template <typename S>
struct tiny_erase<S,2,3> : tiny<typename S::t0, typename S::t1> { };

namespace boost {
namespace mpl {

/// @brief Use our tiny_erase to form the new sequence in O(1) time.
template<>
struct erase_impl<tiny_tag>
{
    template <typename S, typename First, typename Last>
    struct apply { };

    // We have no end, so ask to delete [First, First+1)...
    template <typename S, typename First>
    struct apply<S, First, mpl_::na /* ??? */>
        : apply<S, First, typename boost::mpl::next<First>::type> { };

    template <typename S, typename First, typename Last>
    struct apply< S, tiny_iterator<S, First>, tiny_iterator<S, Last> >
        : tiny_erase<S, First::value, Last::value> { };
};

/// @brief This forwards operation to the erase metafunction.
template<>
struct pop_back_impl<tiny_tag>
{
    template <typename S>
    struct apply
        : erase_impl<tiny_tag>::template apply<
            S,
            typename prior<typename end<S>::type>::type,
            typename end<S>::type> { };
};

/// @brief This forwards operation to the erase metafunction.
template<>
struct pop_front_impl<tiny_tag>
{
    template <typename S>
    struct apply
        : erase_impl<tiny_tag>::template apply<
            S,
            typename begin<S>::type,
            typename next<typename begin<S>::type>::type> { };
};

} // namespace mpl
} // namespace boost

#endif // CHAPTER_5_TINY
