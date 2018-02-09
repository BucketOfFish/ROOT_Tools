#enter name of our code library and the program files
ILIBNAME=run_plots #Enter name of your library here
#enclose multiple programs in quotes
PROGRAMS='$(subst .C,, $(shell cd ./; ls *.C 2>/dev/null))'
SRCS = $(shell ls *.C 2>/dev/null)
OBJ= $(foreach PP, $(PROGRAMS), $(PP).o)

LD=g++

INCLUDEFLAGS = -I$(ROOTCOREDIR)/include/

LD_FLAGS = -L$(ROOTCOREDIR)/lib/$(ROOTCORECONFIG) -lxAODTruth -lxAODRootAccess -lxAODCore -lAthContainers -lCxxUtils -lxAODEventFormat -lAthLinks -lxAODRootAccessInterfaces -lxAODEventInfo #-L./ -lmycode

ROOTLIBS = `root-config --libs`
ROOTCFLAGS = $(shell root-config --cflags)
ROOTGLIBS = $(shell root-config --glibs)

.cxx.o:
	$(CXX) $(CXXFLAGS) $(ROOTCFLAGS) $(INCLUDEFLAGS) -c $<

all: $(PROGS)
	$(CXX) run_plots.C $(CXXFLAGS) -D XAOD_STANDALONE $(ROOTCFLAGS) $(INCLUDEFLAGS) -c $<
	$(LD) -o run_plots run_plots.o $(LD_FLAGS) $(ROOTLIBS) -m64
