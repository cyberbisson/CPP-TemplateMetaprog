// ===-- chapter-6/exercise-6-0.hpp ----------------------- -*- C++ -*- --=== //
/**
 * @file
 * @brief Find the smallest type in a sequence with boost::mpl::copy.
 *
 * <pre>
 * 6-0. Use mpl::copy with a hand-built inserter to write a smallest
 *      metafunction that finds the smallest of a sequence of types.  That is:
 *
 * BOOST_STATIC_ASSERT((
 *     boost::is_same<
 *         smallest< mpl::vector<int[2], char, double&> >::type,
 *         char
 *     >::value
 * ));
 *
 * Now that you've done it, is it a good way to solve that problem?  Why or why
 * not?
 * </pre>
 *
 * @author Matt Bisson
 */

#ifndef EXERCISE_6_0
#define EXERCISE_6_0

#include <boost/static_assert.hpp>

#include <boost/mpl/copy.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/vector.hpp>
using namespace boost::mpl::placeholders;

/// @brief Provide a type to return if the sequence is empty (no "small" type).
struct no_type { };

/**
 * @brief Find the type with a smaller size in bytes.
 *
 * If sizeof T1 < sizeof T2, this returns T1.  Otherwise, it returns T2.
 *
 * @tparam The first type to examine.
 * @tparam The second type to examine.
 *
 * @todo I wonder if there's an MPL function to measure sizes...
 */
template <typename T1, typename T2>
struct find_smaller
    : boost::mpl::if_<boost::mpl::bool_<(sizeof(T1) < sizeof(T2))>, T1, T2> { };

/**
 * @brief Specialize the initial case.
 *
 * We never see no_type unless the sequence we're searching is empty.
 */
template <typename T2>
struct find_smaller<no_type, T2>
{
    typedef T2 type;
};

/**
 * @brief This is our "inserter."  It really just replaces instead of inserting,
 *        though.
 *
 * @tparam State     Result of the last thing...
 * @tparam Operation find_smaller(State, current_item)
 */
template <typename State = no_type, typename Operation = find_smaller<_, _> >
struct replace_with_smaller
{
    typedef Operation operation;
    typedef State state;
};

/**
 * @brief This is the metafunction that returns the smallest type in the
 *        sequence.
 *
 * This could be improved to create a vector when there are multiple types of
 * the same size, all of which are smallest.
 *
 * @tparam S The set of types to examine for smallest size.
 */
template <typename S>
struct smallest : boost::mpl::copy< S, replace_with_smaller<> > { };

// -- Is it a good way to solve the problem?  It's not too bad; perhaps
//    boost::mpl::accumulate would be better as it eliminates the need for the
//    inserter, thus removing a pretty boring pass-through type
//    (replace_with_smaller), and removing the confusing name, "copy", when
//    we're really doing a iterative traversal and returning a single value.

BOOST_STATIC_ASSERT((
    boost::is_same<
        smallest< boost::mpl::vector<int[2], char, double&> >::type,
        char
    >::value
));
BOOST_STATIC_ASSERT((
    boost::is_same<
        smallest< boost::mpl::vector<int, char[20], double&> >::type,
        int
    >::value
));
BOOST_STATIC_ASSERT((
    boost::is_same<smallest< boost::mpl::vector<> >::type, no_type>::value
));

#endif // EXERCISE_6_0
