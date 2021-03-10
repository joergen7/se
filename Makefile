CXX      := g++-10
CXXFLAGS := -Wall -Wextra -pedantic -std=c++20
LDLIBS   :=
LEX      := flex
LFLAGS   :=
YACC     := bison
YFLAGS   :=

GOAL     := a.out
SRC      := se.cc main.cc se.tab.cc se.lex.cc
DEPFILE  := dep.mk

.PHONY : all
all : $(GOAL)

.PHONY : clean
clean :
	$(RM) $(GOAL)
	$(RM) *.o
	$(RM) se.tab.*
	$(RM) se.lex.*
	$(RM) location.hh
	$(RM) stack.hh
	$(RM) position.hh
	$(RM) $(DEPFILE)

$(GOAL): $(SRC:%.cc=%.o)
	$(CXX) -o $@ $(LDLIBS) $^

se.tab.cc se.tab.hh locations.hh stack.hh position.hh &: se.yy
	$(YACC) -d $(YFLAGS) $<

se.lex.cc se.lex.hh &: se.ll
	$(LEX) -o se.lex.cc --header-file=se.lex.hh $(LFLAGS) $<

$(DEPFILE): $(SRC)
	$(CXX) -o $@ -MM -MG $^

include $(DEPFILE)