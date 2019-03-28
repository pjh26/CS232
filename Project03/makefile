# Makefile for Shell Project

# *****************************************************
# Variables to control Makefile operation

CXX = g++
CXXFLAGS = -Wall -g

# ****************************************************
# Targets needed to bring the executable up to date

project: main.o
	$(CXX) $(CXXFLAGS) -o project main.o

# The main.o target can be written more simply

main.o: main.cpp Path.h Prompt.h
	$(CXX) $(CXXFLAGS) -c main.cpp
