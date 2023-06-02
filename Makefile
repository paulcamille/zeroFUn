CXX      ?= g++
CXXFLAGS ?= -std=c++20
CPPFLAGS ?= -O3 -Wall -I. -Wno-conversion-null -Wno-deprecated-declarations

LDFLAGS ?= 
LDLIBS  ?= 

# Flags for the muParser example.
CPPFLAG_MUPARSER ?= -I./ -I./include
EXEC_MUPARSER     = main_getpot_muparser
LDFLAGS_MUPARSER ?= -L./lib -Wl,-rpath=./lib
LIB_MUPARSER     ?= -lmuparser

HEADERS = solverParam.hpp solverTraits.hpp solverBase.hpp secant.hpp secant.hpp solverFactory.hpp


all: $(EXEC_MUPARSER)

%.o: %.cpp 
	$(CXX) -c $(CPPFLAGS) $(CXXFLAGS) $<

$(EXEC_MUPARSER).o: %.o: %.cpp  muparser_fun.hpp
	$(CXX) -c $(CPPFLAGS) $(CPPFLAG_MUPARSER) $(CXXFLAGS) $<


$(EXEC_MUPARSER): %: %.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(LDFLAGS_MUPARSER) $< $(LIBS) $(LIB_MUPARSER) -o $@

clean:
	$(RM) *.o

distclean: clean
	$(RM) $(EXEC_MUPARSER)
	$(RM) *~
