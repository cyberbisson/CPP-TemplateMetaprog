// ===-- chapter-3/exercise-3-5.hpp ----------------------- -*- C++ -*- --=== //
/**
 * @file
 * @brief Add multiplication and division that honors units of measurement.
 *
 * <pre>
 * 3-5. There's still a problem with the dimensional analysis code in section
 *      3.1.  Hint: What happens when you do:
 *          f = f + m * a;
 *      Repair this example using techniques shown in this chapter.
 * </pre>
 *
 * @author Matt Bisson
 */

#ifndef EXERCISE_3_5
#define EXERCISE_3_5

#include <boost/static_assert.hpp>

#include <boost/mpl/equal.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/vector_c.hpp>

#include <boost/mpl/placeholders.hpp>
using namespace boost::mpl::placeholders;

/// @brief Modification of algorithms from Chapter 3, Section 1.
namespace section_3_1
{

// No units!
typedef boost::mpl::vector_c<int, 0, 0, 0, 0, 0, 0, 0> scalar;

// Simple dimensions
typedef boost::mpl::vector_c<int, 1, 0, 0, 0, 0, 0, 0> mass;
typedef boost::mpl::vector_c<int, 0, 1, 0, 0, 0, 0, 0> length;
typedef boost::mpl::vector_c<int, 0, 0, 1, 0, 0, 0, 0> time;
typedef boost::mpl::vector_c<int, 0, 0, 0, 1, 0, 0, 0> charge;
typedef boost::mpl::vector_c<int, 0, 0, 0, 0, 1, 0, 0> temperature;
typedef boost::mpl::vector_c<int, 0, 0, 0, 0, 0, 1, 0> intensity;
typedef boost::mpl::vector_c<int, 0, 0, 0, 0, 0, 0, 1> amount_of_substance;

// More complicated units
typedef boost::mpl::vector_c<int, 0, 1, -1, 0, 0, 0, 0> velocity;
typedef boost::mpl::vector_c<int, 0, 1, -2, 0, 0, 0, 0> acceleration;
typedef boost::mpl::vector_c<int, 1, 1, -1, 0, 0, 0, 0> momentum;
typedef boost::mpl::vector_c<int, 1, 1, -2, 0, 0, 0, 0> force;

/**
 * @brief A numerical quanitity with intrinsic dimensions.
 *
 * To prevent accidental arithmetic between quantities that make no sense, we
 * inlclude the units/dimensions for context.  Thus, you cannot add 5 meters to
 * 10 degrees and get a result.
 *
 * @tparam T The storage container for the numerical value.
 * @tparam Dimensions One of the dimension types (e.g., mass, length, force).
 */
template <typename T, typename Dimension>
class quantity
{
public:
    /**
     * @brief Construct this quantity with an initial value.
     * @param[in] x The initial value for this quantity.
     */
    explicit quantity(T x)
        : m_value(x) { }

    /**
     * @brief Construct a quantity from another quantity with (possibly)
     *     different dimensions.
     *
     * Check at compile time for equal dimensions, or we will lose the whole
     * point of creating this class template.
     *
     * @tparam OtherDimensions
     *     Dimensions that must be identical to, or convertable to the current
     *     quantity's dimensions.
     * @param[in] rhs The quantity to copy.
     */
    template <typename OtherDimension>
    quantity(quantity<T,OtherDimension> const& rhs)
        : m_value(rhs.value())
    {
        BOOST_STATIC_ASSERT(
            (boost::mpl::equal<Dimension,OtherDimension>::type::value));
    }

    /// @brief Return the current quantity's value.
    T value() const { return m_value; }

private:
    /// @brief The current value of this quantity.
    T m_value;
};

// Exercise 3-5 requires the addition of D2, allowing the addition of
// equivalent matrices with non-directly-convertable types.

/**
 * @brief Add two quantities.
 *
 * @tparam T  The container type for the quantity's value.
 * @tparam D1 The quantity's resulting dimensions.
 * @tparam D2 Dimensions for an input quantity that are compatible with the
 *            output dimensions.
 *
 * @param[in] x The first quantity to add.
 * @param[in] y The second quantity to add.
 *
 * @return A new quantity with the same dimensions as the first input quantity
 *     whose value is the sum of both input quantities.
 */
template <typename T, typename D1, typename D2>
quantity<T,D1> operator+(quantity<T,D1> x, quantity<T,D2> y)
{
    BOOST_STATIC_ASSERT((boost::mpl::equal<D1,D2>::type::value));
    return quantity<T,D1>(x.value() + y.value());
}

/**
 * @brief Subtract two quantities.
 *
 * @tparam T  The container type for the quantity's value.
 * @tparam D1 The quantity's resulting dimensions.
 * @tparam D2 Dimensions for an input quantity that are compatible with the
 *            output dimensions.
 *
 * @param[in] x The first quantity to subtract.
 * @param[in] y The second quantity to subtract.
 *
 * @return A new quantity with the same dimensions as the first input quantity
 *     whose value is the difference of both input quantities.
 */
template <typename T, typename D1, typename D2>
quantity<T,D1> operator-(quantity<T,D1> x, quantity<T,D2> y)
{
    return quantity<T,D1>(x.value() - y.value());
}

// Exercise 3-5: Let's allow multiplication and division of quantities by
// processing their dimensions.

/**
 * @brief Divide all elements of two dimension sequences.
 *
 * Create a sequence that contains all the elements of the first sqeuence
 * divided by all the elements of the second sequence.
 *
 * @tparam D1 The first demension.
 * @tparam D2 The second demension.
 */
template<typename D1, typename D2>
struct divide_dimensions
    : boost::mpl::transform<D1,D2,boost::mpl::minus<_1,_2> > { };

/**
 * @brief Multiply all elements of two dimension sequences.
 *
 * Create a sequence that contains all the elements of the first sqeuence
 * multiplied by all the elements of the second sequence.
 *
 * @tparam D1 The first demension.
 * @tparam D2 The second demension.
 */
template<typename D1, typename D2>
struct multiply_dimensions
    : boost::mpl::transform<D1,D2,boost::mpl::plus<_1,_2> > { };

/**
 * @brief Multiply two quantities.
 *
 * @tparam T  The container type for the quantity's value.
 * @tparam D1 The first quantity's dimensions.
 * @tparam D2 The second quantity's dimensions.
 *
 * @param[in] x The first quantity to multiply.
 * @param[in] y The second quantity to multiply.
 *
 * @return A new quantity whose value is a product of the inputs, and whose
 *     dimensions are similarly a product of the inputs' dimensions.
 */
template <typename T, typename D1, typename D2>
quantity<T, typename multiply_dimensions<D1,D2>::type>
operator*(quantity<T,D1> x, quantity<T,D2> y)
{
    return quantity<T, typename multiply_dimensions<D1,D2>::type>(
        x.value() * y.value());
}

/**
 * @brief Divide two quantities.
 *
 * @tparam T  The container type for the quantity's value.
 * @tparam D1 The first quantity's dimensions.
 * @tparam D2 The second quantity's dimensions.
 *
 * @param[in] x The first quantity to divide.
 * @param[in] y The second quantity to divide.
 *
 * @return A new quantity whose value is a quotient of the inputs, and whose
 *     dimensions are similarly a quotient of the inputs' dimensions.
 */
template <typename T, typename D1, typename D2>
quantity<T, typename divide_dimensions<D1,D2>::type>
operator/(quantity<T,D1> x, quantity<T,D2> y)
{
    return quantity<T, typename divide_dimensions<D1,D2>::type>(
        x.value() / y.value());
}

} // namespace section_3_1

#endif // EXERCISE_3_5
