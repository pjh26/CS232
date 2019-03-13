# Makefile for CallTimer Project

# *****************************************************
# Variables to control Makefile operation

CXX = g++
CXXFLAGS = -Wall -g -pthread

# ****************************************************
# Targets needed to bring the executable up to date

callTimer: main.o
	$(CXX) $(CXXFLAGS) -o callTimer main.o

# The main.o target can be written more simply

main.o: main.cpp CMDController.h CMDInterface.h TXTController.h TXTInterface.h CallTimer.h NanoTimer.h Interface.h
	$(CXX) $(CXXFLAGS) -c main.cpp
