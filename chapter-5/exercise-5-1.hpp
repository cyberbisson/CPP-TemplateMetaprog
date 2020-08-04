// ===-- chapter-5/exercise-5-1.hpp ----------------------- -*- C++ -*- --=== //
/**
 * @file
 * @brief Double the numbers in the first half of a RandomAccessSequence.
 *
 * <pre>
 * 5-1. Write a metafunction double_first_half that takes a RandomAccessSequence
 *      of integral constant wrappers of length N as an argument, and returns a
 *      copy with the first N/2 elements doubled in value, such that the
 *      following is true:
 *
 *      mpl::equal<
 *          double_first_half< mpl::vector_c<int,1,2,3,4> >::type,
 *          mpl::vector_c<int,2,4,3,4>
 *      >::type::value
 * </pre>
 *
 * @author Matt Bisson
 */

#ifndef EXERCISE_5_1
#define EXERCISE_5_1

#include <boost/static_assert.hpp>

#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/equal.hpp>
#include <boost/mpl/greater_equal.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/mpl/times.hpp>
#include <boost/mpl/vector_c.hpp>

/**
 * @brief Represents a single iteration across the sequence.
 *
 * This metafunction computes the mid-point, decides what operation to perform
 * on the element, folds the result into the destination, and kicks off the next
 * iteration.  This is part of the algorithm for double_first_half.
 *
 * @tparam S   The input sequence (needed to measure distances).
 * @tparam Res The resulting sequence.
 * @tparam Cur The iterator to the current location in S.
 */
template <typename S, typename Res, typename Cur>
class double_first_half_impl
{
    // Better to break up the algorithm a bit and make things clearer...

    /// @brief The distance from the beginning of the sequence to where we are.
    typedef boost::mpl::distance<typename boost::mpl::begin<S>::type, Cur>
    dist_to_begin;

    /// @brief The distance from the end of the sequence to where we are.
    typedef boost::mpl::distance<Cur, typename boost::mpl::end<S>::type>
    dist_to_end;

    /// @brief Lazily decide what operation to use if we're past the midpoint.
    typedef
    boost::mpl::eval_if<
        boost::mpl::greater_equal<dist_to_begin, dist_to_end>,
        boost::mpl::deref<Cur>,
        boost::mpl::times<
            typename boost::mpl::deref<Cur>::type,
            boost::mpl::int_<2>
        >
    > multiply_or_not;

public:
    /// @brief Produce a result and keep iterating until we reach the end.
    typedef
    typename
    boost::mpl::eval_if<
        boost::is_same<Cur, typename boost::mpl::end<S>::type>,
        Res,
        double_first_half_impl<
            S,
            typename boost::mpl::push_back<
                Res,
                typename multiply_or_not::type
            >::type,
            typename boost::mpl::next<Cur>::type
        >
    >::type type;
};

/**
 * @brief Double the values in the first half of the given sequence.
 *
 * Takes a RandomAccessSequence of integral constant wrappers of length N as an
 * argument, and returns a copy with the first N/2 elements doubled in value.
 *
 * @tparam S The sequence to transform.
 */
// Interesting note: double_first_half results in the following (with
// boost::mpl::vector_c<int, 1, 2, 3, 4> as input):
//
//     boost::mpl::v_item<
//         mpl_::integral_c<int, 4>,
//         boost::mpl::v_item<
//             mpl_::integral_c<int, 3>,
//             boost::mpl::v_item<
//                 mpl_::integral_c<int, 4>,
//                 boost::mpl::v_item<
//                     mpl_::integral_c<int, 2>,
//                     boost::mpl::vector_c<int>,
//                 0>,
//             0>,
//         0>,
//     0>
// This is boost::mpl::equal to boost::mpl::vector_c<int, 2, 4, 3, 4>
template <typename S>
struct double_first_half
    : double_first_half_impl<
        S, boost::mpl::vector_c<int>, typename boost::mpl::begin<S>::type>
{ };

typedef boost::mpl::vector_c<int, 1, 2, 3, 4> testVec;

typedef double_first_half<testVec>::type testVec2;
BOOST_STATIC_ASSERT((boost::mpl::equal<
                     testVec2,
                     boost::mpl::vector_c<int, 2, 4, 3, 4> >::value));

#endif
