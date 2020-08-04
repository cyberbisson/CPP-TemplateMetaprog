// ===-- chapter-7/exercise-7-2.hpp ----------------------- -*- C++ -*- --=== //
/**
 * @file
 * @brief Modify zip_iterator category to be "least refined."
 *
 * <pre>
 * 7-2. Modify your zip_iterator so that its iterator category reflects the
 *      least-refined concept modeled by any of its underlying iterators.
 *      Extend the iterator implementation to satisfy all potential requirements
 *      of the computed category.
 * </pre>
 *
 * @author Matt Bisson
 */

#ifndef EXERCISE_7_2
#define EXERCISE_7_2

// See chapter-7-zip_view.hpp for the real work
#include "chapter-7-zip_view.hpp"

#ifndef SKIP_TEST

#include <boost/mpl/list.hpp>
#include <boost/mpl/list_c.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/vector_c.hpp>

typedef boost::mpl::vector_c<int, 1, 3, 5, 7> v1;
typedef boost::mpl::vector_c<int, 2, 4, 6, 8> v2;
typedef boost::mpl::vector<v1, v2> zip_vec;
typedef ::zip_view<zip_vec> zip_vec_t;
typedef least_refined_iterator_category<zip_vec>::type zip_vec_category;
BOOST_STATIC_ASSERT((
    boost::is_same<
        zip_vec_category,
        boost::mpl::random_access_iterator_tag
    >::value));

typedef boost::mpl::begin<zip_vec_t>::type zv_begin;
typedef boost::mpl::deref<zv_begin>::type zv_begin_t;
BOOST_STATIC_ASSERT((
    boost::mpl::equal<
        zv_begin_t, boost::mpl::vector_c<int, 1, 2>
    >::value));
typedef boost::mpl::next<zv_begin>::type zv_next;
BOOST_STATIC_ASSERT((
    boost::mpl::equal<
        boost::mpl::deref<zv_next>::type, boost::mpl::vector_c<int, 3, 4>
    >::value));
typedef boost::mpl::prior<zv_next>::type zv_prior;
BOOST_STATIC_ASSERT((boost::is_same<zv_prior, zv_begin>::value));
BOOST_STATIC_ASSERT((
    boost::mpl::equal<
        boost::mpl::deref<zv_prior>::type, boost::mpl::vector_c<int, 1, 2>
    >::value));
typedef boost::mpl::at< zip_vec_t, boost::mpl::int_<2> >::type zv_at2;
BOOST_STATIC_ASSERT((
    boost::mpl::equal<
        boost::mpl::deref<zv_at2>::type, boost::mpl::vector_c<int, 5, 6>
    >::value));

typedef boost::mpl::advance< zv_next, boost::mpl::int_<2> >::type zv_at3;
BOOST_STATIC_ASSERT((
    boost::mpl::equal<
        boost::mpl::deref<zv_at3>::type, boost::mpl::vector_c<int, 7, 8>
    >::value));

typedef boost::mpl::list_c<int, 1, 3, 5, 7> l1;
typedef boost::mpl::list_c<int, 2, 4, 6, 8> l2;
typedef boost::mpl::list<l1, l2> zip_list;
typedef least_refined_iterator_category<zip_list>::type zip_list_category;
BOOST_STATIC_ASSERT((
    boost::is_same<
        zip_list_category,
        boost::mpl::forward_iterator_tag
    >::value));

#endif // !SKIP_TEST

#endif // EXERCISE_7_2
