# CXX=g++ 
# CXXFLAGS=-std=c++2a -Wall -O -g -MMD -Werror=vla # use -MMD to generate dependencies
# SOURCES=$(wildcard *.cc)   # list of all .cc files in the current directory
# OBJECTS=${SOURCES:.cc=.o}  # .o files depend upon .cc files with same names
# DEPENDS=${OBJECTS:.o=.d}   # .d file is list of dependencies for corresponding .cc file
# EXEC=watopoly

# # First target in the makefile is the default target.
# $(EXEC): $(OBJECTS)
# 	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(EXEC)

# %.o: %.cc 
# 	$(CXX) -c -o $@ $< $(CXXFLAGS) 

# -include ${DEPENDS}

# .PHONY: clean
# clean:
# 	rm  -f $(OBJECTS) $(DEPENDS) $(EXEC)

CXX=g++
CXXFLAGS=-std=c++2a -Wall -O2 -g -MMD -Werror=vla
SOURCES=$(wildcard *.cc)
OBJECTS=$(SOURCES:.cc=.o)
DEPENDS=$(OBJECTS:.o=.d)
EXEC=watopoly

# Default target
$(EXEC): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(EXEC)

# Rules for compiling .cc files into .o files
%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Include dependencies
-include $(DEPENDS)

# Clean target
.PHONY: clean
clean:
	rm -f $(OBJECTS) $(DEPENDS) $(EXEC)

