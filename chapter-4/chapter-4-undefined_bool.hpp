/**
 * @file
 * @brief Define some booleans that don't compile on either true or false.
 *
 * Create some types that evaluate in one case, and produce a compilation error
 * in the other.
 *
 * @author Matt Bisson
 */

#ifndef CHAPTER_4_UNDEFINED_BOOL
#define CHAPTER_4_UNDEFINED_BOOL

/**
 * @brief If the template parameter is false, template instantiation is an error.
 */
template <bool B> struct undefined_false;

/// @brief Define this metafunction if specialized to true.
template <> struct undefined_false<true>
{
    static bool const value = true;
    typedef undefined_false<true> type;
};


/**
 * @brief If the template parameter is true, template instantiation is an error.
 */
template <bool B> struct undefined_true;

/// @brief Define this metafunction if specialized to false.
template <> struct undefined_true<false>
{
    static bool const value = false;
    typedef undefined_true<false> type;
};

#endif // CHAPTER_4_UNDEFINED_BOOL
