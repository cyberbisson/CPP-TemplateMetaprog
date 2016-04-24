/**
 * @file
 * @brief Implement rotate_view sequence view.
 *
 * <pre>
 * 7-3. Use mpl::joint_view to implement a rotate_view sequence view, presenting 
 *      a shifted and wrapped view onto the original sequence:
 *
 * typedef mpl::vector_c<int,5,6,7,8,9,0,1,2,3,4> v;
 * typedef rotate_view<
 *     v,
 *     mpl::advance_c<mpl::begin<v>::type,5>::type
 * > view;
 *
 * BOOST_STATIC_ASSERT((
 *     mpl::equal<
 *     view, mpl::range_c<int,0,10>
 * >::value ));
 * </pre>
 *
 * @author Matt Bisson
 */

#ifndef EXERCISE_7_3
#define EXERCISE_7_3

#include <boost/mpl/advance.hpp>
#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/iterator_range.hpp>
#include <boost/mpl/joint_view.hpp>

/**
 * @brief A shifted and wrapped view onto the original sequence.
 *
 * @tparam S      The original sequence.
 * @tparam Offset Offset into the original sequence where the view should begin.
 *
 * @note The presense of joint_view::tag etc will give us those operations for
 *       free if we directly inherit...
 */
template <typename S, typename Offset>
struct rotate_view
    : boost::mpl::joint_view<
        boost::mpl::iterator_range<Offset, typename boost::mpl::end<S>::type>,
        boost::mpl::iterator_range<typename boost::mpl::begin<S>::type, Offset>
    >
{ };

#include <boost/static_assert.hpp>
#include <boost/mpl/equal.hpp>
#include <boost/mpl/range_c.hpp>
#include <boost/mpl/vector_c.hpp>

typedef boost::mpl::vector_c<int,5,6,7,8,9,0,1,2,3,4> v;
typedef rotate_view<
    v,
    boost::mpl::advance_c<boost::mpl::begin<v>::type, 5>::type
> view;

BOOST_STATIC_ASSERT((
    boost::mpl::equal< view, boost::mpl::range_c<int, 0, 10> >::value));


#endif // EXERCISE_7_3
