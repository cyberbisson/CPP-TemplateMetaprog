// ===-- main.hpp ----------------------------------------- -*- C++ -*- --=== //
/**
 * @file
 * @brief This file exists as a home for generated documentation.
 * @author Matt Bisson
 */

/**
 * @mainpage
 *
 * This package tracks my attempts at completing the exercises on the book, "C++
 * Template Metaprogramming: Concepts, Tools, and Techniques from Boost and
 * Beyond" by David Abrahams and Aleksey Gurtovoy.  I do know if one other place
 * where solutions may be found for these exercises
 * (http://www.crystalclearsoftware.com/cgi-bin/boost_wiki/wiki.pl?CPP_Template_Metaprogramming_Book_-_Answers_Page)
 * --- but since some exercises within the book build upon the answers from
 * other exercises, I elected @em not to place my answers in that location so I
 * could structure my code for re-use, and ensure it was easily compilable and
 * maintainable.
 *
 * # Layout #
 *
 * @b Start @b with @b the @b "Files" @b list --- the file structure very much
 * mirrors the book structure (if you're looking at the solutions in the
 * generated documentation, make sure to "Go to the source code...").  Each
 * chapter has its own main file with a name like "chapter-n.cpp", and exists
 * within a directory named "chapter-n" (where @em n corresponds to a chapter
 * number in the book, of course).  Within this area, each exercise with a
 * (non-trivial) amount of code in its solution exists in a file with a name
 * like "exercise-n-x.hpp" (where @em n is the chapter, and @em x is the
 * exercise number).  If this exercise file doesn't exist, the exercise is most
 * likely a simple test-writing exercise, or a written one.  Those solutions
 * exist in the main chapter file.
 *
 * # Building and Running #
 *
 * There are a few useful make targets:
 * @li "all": This builds all the executables for each chapter.  Since this is a
 *     template metaprogramming exercise, some executables actually do very
 *     little at run-time, but building the executables does the important
 *     stuff, like compile all the C++ headers and sources.  This target can be
 *     configured to use the CLang compiler or the GNU C++ compiler by setting
 *     @c USE_CLANG as an environment variable.  Additionally, all output is in
 *     "release" format, unless your environment has @c USE_DEBUG set.  The
 *     compiler must be in the path.
 * @li "docs": This builds the generated documentation that you are currently
 *     reading.  Doxygen must be in the path.
 * @li "gtags": This finds relevant files and generates a source-code "tag"
 *     database for GNU global.  The "gtags" executable must be in the path.
 * @li "clean": Removes executables and other object files.
 * @li "clean_docs": Deletes the generated documentation.
 * @li "clean_gtags": Removes files generated by gtags.
 * @li "distclean": Removes all derived objects from any target.  This is useful
 *      for creating a "pristine" source tree for posterity.
 *
 * The make targets place executables (for each chapter) in the root of the
 * samples tree under the naming convention "run-chapter-n" (where @em n is the
 * chapter in question).
 *
 * # Enjoy! #
 *
 * I hope you have as much fun learning from this book as I did.  I definitely
 * recommend only consulting with someone else's answers if you a) have no idea
 * what the question is trying to ask, or b) you already have implemented the
 * right answer.  The hardest struggles among the exercises here led to my best
 * understanding, so have fun, and good luck!
 *
 * @author Matt Bisson
 * @date February 12, 2014 -- May 15, 2014
 */

#ifndef MAIN_HPP
#define MAIN_HPP

/// @brief Exists to inject functionality into the Boost namespace.
namespace boost
{

/// @brief Exists to inject functionality into the Boost MPL namespace.
namespace mpl
{

} // namespace mpl
} // namespace boost

#endif // MAIN_HPP
