
/**
 * @file
 * @brief Chapter 7: Views and Iterators Adaptors
 *
 * C++ Template Metaprogramming: Concepts, Tools, and Techniques from Boost
 * and Beyond.
 *
 * @author Matt Bisson - 5/15/2014
 */

#include "exercise-7-0.hpp"

/**
 * @file
 *
 * Additional Exercises:
 *
 * <pre>
 * 7-1. Our implementation of zip_iterator uses transform to generate its nested
 *      ::type.  Would using transform_view instead yield any advantages in this
 *      case?
 * </pre>
 */

// transform_view might yield some benefit if the caller doesn't examine all the
// elements in the "zipped" element, but this is a strange case -- it's unlikely
// someone would zip the contents of multiple sequences and only look at a
// subset of those sequences when iterating.

#include "exercise-7-2.hpp"
#include "exercise-7-3.hpp"

/**
 * @file
 *
 * <pre>
 * 7-4. Design and implement an iterator adaptor that adapts any Random Access
 *      Iterator by presenting the elements it traverses in an order determined
 *      by a sequence of nonnegative integer indices.  Make your
 *      permutation_iterator a forward iterator.
 * </pre>
 */

/**
 * @file
 *
 * <pre>
 * 7-5. Change the permutation iterator from exercise 7-4 so its traversal
 *      category is determined by the category of the sequence of indices.
 * </pre>
 */

/**
 * @file
 *
 * <pre>
 * 7-6. Implement a permutation_view using your permutation iterator adaptor, so
 *      that:
 *
 * permutation_view<
 *     mpl::list_c<int,2,1,3,0,2>,      // indices
 *     mpl::vector_c<int,11,22,33,44> > // elements
 *
 *      yields sequence [33,22,44,11,33]
 * </pre>
 */

#include "chapter-7-permutation_view.hpp"

#include <boost/static_assert.hpp>
#include <boost/mpl/equal.hpp>
#include <boost/mpl/list_c.hpp>
#include <boost/mpl/vector_c.hpp>

typedef permutation_view<
    boost::mpl::list_c<int,2,1,3,0,2>,    // indices
    boost::mpl::vector_c<int,11,22,33,44> // elements
> pv1;

typedef boost::mpl::begin<pv1>::type it0;
typedef boost::mpl::deref<it0>::type val0;
BOOST_STATIC_ASSERT((33 == val0::value));

typedef boost::mpl::next<it0>::type it1;
typedef boost::mpl::deref<it1>::type val1;
BOOST_STATIC_ASSERT((22 == val1::value));

BOOST_STATIC_ASSERT((
    boost::mpl::equal< pv1, boost::mpl::vector_c<int,33,22,44,11,33> >::value));

#include "exercise-7-7.hpp"

/**
 * @file
 *
 * <pre>
 * 7-8. Implement a crossproduct_view template that adapts two original
 *      sequences by presenting all possible pairs of their elements in a right
 *      cross product order.
 * </pre>
 */

int main()
{
    return 0;
}
