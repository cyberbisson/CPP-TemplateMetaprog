/**
 * @file
 * @brief Rewrite twice as a lambda.
 *
 * <pre>
 * 3-6. Build a lambda expression that has functionality equivalent to twice.
 *      Hint: mpl::apply is a metafunction!
 * </pre>
 *
 * @author Matt Bisson
 */

#ifndef EXERCISE_3_6
#define EXERCISE_3_6

#include <boost/mpl/apply.hpp>

/// @brief A lambda to perform a metafunction twice.
struct twice_lambda
{
    /**
     * @brief When applied, performs the given function twice.
     *
     * @tparam F A unary metafunction to invoke.
     * @tparam X The initial input passed to F.
     */
    template <typename F, typename X>
    struct apply
        : boost::mpl::apply<F, typename boost::mpl::apply<F, X>::type> { };
};

#endif // EXERCISE_3_6
