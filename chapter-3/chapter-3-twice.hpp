// ===-- chapter-3/chapter-3-twice.hpp -------------------- -*- C++ -*- --=== //
/**
 * @file
 * @brief Define the twice metafunction for use in multiple exercises.
 *
 * @author Matt Bisson
 */

#ifndef CHAPTER_3_TWICE
#define CHAPTER_3_TWICE

#include <boost/mpl/apply.hpp>

/**
 * @brief Apply a metafunction to its own result.
 *
 * In other words, this will perform F(F(X)).
 *
 * @tparam F The unary metafunction to apply.
 * @tparam X The initial value to send to the metafunction.
 */
template <typename F, typename X>
struct twice : boost::mpl::apply<F, typename boost::mpl::apply<F, X>::type> { };

#endif // CHAPTER_3_TWICE
