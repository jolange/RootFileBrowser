MAKEFLAGS = --no-print-directory -r -s

INCLUDE = $(shell root-config --cflags) -I./src -I.
LIBS    = $(shell root-config --glibs)

CXX = g++ -Wall -Wshadow

BIN = RootFileBrowser

SRCDIR=src
OBJDIR=build
EXTDIR=3rdParty

SRCS   = RootFileBrowser.cpp
EXTSRCS= TAppKillManager.cpp

OBJS = $(SRCS:%.cpp=$(OBJDIR)/%.o) $(EXTSRCS:%.cpp=$(OBJDIR)/%.o) $(EXTSRCS:%.cpp=$(OBJDIR)/%_dict.o)

.PHONY: all clean

all: $(OBJDIR) $(BIN)

# == Building and Linking ==
$(BIN): $(OBJS)
	@echo -n "Linking  $@... "
	$(CXX) -o $@ $^ $(LIBS)
	@echo "done"

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@echo -n "Building $(@F)..."
	$(CXX) -c $(INCLUDE) $(LIBS) -o $@ $<
	@echo " done"

$(OBJDIR)/%.o: $(EXTDIR)/%.cpp $(EXTDIR)/%.hpp
	@echo -n "Building $(@F)..."
	$(CXX) -c $(INCLUDE) $(LIBS) -o $@ $<
	@echo " done"

$(OBJDIR)/%_dict.o: $(OBJDIR)/%_dict.cpp
	@echo -n "Building $(@F)..."
	$(CXX) -c $(INCLUDE) $(LIBS) -o $@ $<
	@echo " done"

$(OBJDIR)/%_dict.cpp: $(EXTDIR)/%.hpp
	@echo -n Creating $(@F)
	rootcint -l -f $@ -c $<
	# remove the paths in the includes (can't tell rootcint this...)
	# ok, don't need this with "-I." ...
	#sed -i s?$(OBJDIR)/??g $(@D)/$(*F)_dict.h
	#sed -i s?$(EXTDIR)/??g $(@D)/$(*F)_dict.h
	#sed -i s?$(OBJDIR)/??g $@
	#sed -i s?$(EXTDIR)/??g $@
	@echo " done"

# == Dependencies ==
$(OBJDIR)/RootFileBrowser.o: $(EXTDIR)/TAppKillManager.hpp
$(OBJDIR)/RootFileBrowser_dict.cpp: $(EXTDIR)/TAppKillManager.hpp

$(OBJDIR):
	mkdir -p $@

clean:
	rm -f $(OBJS) $(EXTSRCS:%.cpp=$(OBJDIR)/%_dict.h) $(EXTSRCS:%.cpp=$(OBJDIR)/%_dict.cpp)
