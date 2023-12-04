CXX = g++-11 -std=c++20
CXXFLAGS = -Wall -g -MMD -I/opt/X11/include  # Add the X11 include directory
LDFLAGS = -L/opt/X11/lib -lX11  # Add the X11 library directory and link against libX11
SOURCES = $(wildcard *.cc)   # list of all .cc files in the current directory
OBJECTS = ${SOURCES:.cc=.o}  # .o files depend upon .cc files with same names
DEPENDS = ${OBJECTS:.o=.d}   # .d file is list of dependencies for corresponding .cc file
EXEC=chess

# First target in the makefile is the default target.
$(EXEC): $(OBJECTS)
	$(CXX) $(OBJECTS) $(CXXFLAGS) $(LDFLAGS) -o $(EXEC)

%.o: %.cc
	$(CXX) -c -o $@ $< $(CXXFLAGS)

-include ${DEPENDS}

.PHONY: clean
clean:
	rm  -f $(OBJECTS) $(DEPENDS) $(EXEC)
