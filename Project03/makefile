# Makefile for Shell Project

# *****************************************************
# Variables to control Makefile operation

CXX = g++
CXXFLAGS = -Wall -g

# ****************************************************
# Targets needed to bring the executable up to date

SPShell : main.o Path.o Prompt.o SPShell.o CommandLine.o
	$(CXX) $(CXXFLAGS) -o SPShell main.o Path.o Prompt.o SPShell.o CommandLine.o

# The main.o target can be written more simply

main.o : main.cpp SPShell.h
	$(CXX) $(CXXFLAGS) -c main.cpp

SPShell.o : SPShell.cpp Path.h Prompt.h CommandLine.h
	$(CXX) $(CXXFLAGS) -c SPShell.cpp

Path.o : Path.cpp
	$(CXX) $(CXXFLAGS) -c Path.cpp

Prompt.o : Path.cpp
	$(CXX) $(CXXFLAGS) -c Prompt.cpp

CommandLine.o : CommandLine.cpp
	$(CXX) $(CXXFLAGS) -c CommandLine.cpp
