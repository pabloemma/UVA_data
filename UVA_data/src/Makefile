CC = gcc
CXX = g++
RM = rm -f

CPPFLAGS=-g $(shell root-config --cflags)
LDFLAGS=-g $(shell root-config --ldflags)
LDLIBS=$(shell root-config --libs)

ROOTLIBS='-lRooFit -lHtml -lMinuit -lRooFitCore -lRooStats -lHistFactory'

SRCS = PDPsig.cc
OBJS = $(subst .cc,.o,$(SRCS))

# Assumes that the script is in MyScript.C
# and it must contain a main() function




all: PDPsig

PDPsig: $(OBJS)
	$(CXX) $(LDFLAGS) -o PDPsig $(OBJS) $(LDLIBS)

depend: .depend

.depend: $(SRCS)
	$(RM) ./.depend
	$(CXX) $(CPPFLAGS) -MM $^>>./.depend;

clean:
	$(RM) $(OBJS)
    
distclean: clean
	$(RM) *~ .depend
	
include .depend	

