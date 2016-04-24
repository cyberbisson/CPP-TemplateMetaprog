# Matt Bisson - 2/12/2014
#
# The Makefile is a means to an end... I don't care about how difficult it is
# to maintain.

ifdef USE_CLANG
CXX = clang++
else
CXX = g++
endif

CPPFLAGS = -DUSE_TESTS

CFLAGS = -Wall -Wextra -march=native
ifdef USE_DEBUG
CFLAGS += -g
else
CFLAGS += -O3
endif

CXXFLAGS = $(CFLAGS) -std=c++98

EXES = \
       run-chapter-1 \
       run-chapter-2 \
       run-chapter-3 \
       run-chapter-4 \
       run-chapter-5 \
       run-chapter-6 \
       run-chapter-7

all: $(EXES)

gtags:
	rm -f gtags.files
	find . -name '*.?pp' | grep -v 'main.hpp' | sort >> gtags.files
	gtags --file gtags.files --statistics --verbose

run-chapter-1: chapter-1/chapter-1.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ $<

run-chapter-2: \
        chapter-2/chapter-2.cpp \
        chapter-2/exercise-2-0.hpp \
        chapter-2/exercise-2-1.hpp \
        chapter-2/exercise-2-2.hpp \
        chapter-2/exercise-2-3.hpp \
        chapter-2/exercise-2-4.hpp \
        chapter-2/exercise-2-5.hpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ $<

run-chapter-3: \
        chapter-3/chapter-3.cpp \
        chapter-3/chapter-3-twice.hpp \
        chapter-3/exercise-3-0.hpp \
        chapter-3/exercise-3-1.hpp \
        chapter-3/exercise-3-2.hpp \
        chapter-3/exercise-3-3.hpp \
        chapter-3/exercise-3-4.hpp \
        chapter-3/exercise-3-5.hpp \
        chapter-3/exercise-3-6.hpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ $<

run-chapter-4: \
        chapter-4/chapter-4.cpp \
        chapter-4/chapter-4-undefined_bool.hpp \
        chapter-4/exercise-4-0.hpp \
        chapter-4/exercise-4-1.hpp \
        chapter-4/exercise-4-2.hpp \
        chapter-4/exercise-4-3.hpp \
        chapter-4/exercise-4-4.hpp \
        chapter-4/exercise-4-4.hpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ $<

run-chapter-5: \
        chapter-5/chapter-5.cpp \
        chapter-5/chapter-5-tiny.hpp \
        chapter-5/chapter-5-tree.hpp \
        chapter-5/exercise-5-1.hpp \
        chapter-5/exercise-5-6.hpp \
        chapter-5/exercise-5-7.hpp \
        chapter-5/exercise-5-8.hpp \
        chapter-5/exercise-5-9.hpp \
        chapter-5/exercise-5-10.hpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ $<

run-chapter-6: \
        chapter-6/chapter-6.cpp \
        chapter-6/chapter-6-tree.hpp \
        chapter-6/exercise-6-0.hpp \
        chapter-6/exercise-6-1.hpp \
        chapter-6/exercise-6-3.hpp \
        chapter-6/exercise-6-4.hpp
	$(CXX) $(CPPFLAGS) -Ichapter-5 $(CXXFLAGS) -o $@ $<

run-chapter-7: \
        chapter-7/chapter-7.cpp \
        chapter-7/chapter-7-permutation_view.hpp \
        chapter-7/chapter-7-zip_view.hpp \
        chapter-7/exercise-7-0.hpp \
        chapter-7/exercise-7-2.hpp \
        chapter-7/exercise-7-3.hpp \
        chapter-7/exercise-7-7.hpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ $<

clean:
	rm -rf $(EXES)

docs:
	doxygen Doxyfile

clean_docs:
	rm -rf doc

clean_gtags:
	rm -f GPATH GRTAGS GTAGS gtags.files

distclean: clean clean_docs clean_gtags
