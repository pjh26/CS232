//
//  CommandLine.cpp
//  project03
//
//  Created by Sameer Mall on 3/19/19.
//  Copyright © 2019 Sameer Mall. All rights reserved.
//

#include "CommandLine.h"
#include <iostream>
#include <string.h>
using namespace std;

/*
 * CommandLine() default constructor
 */
CommandLine::CommandLine() {
    argc = 0;
    noAmp = true;
}

/*
 * CommandLine() explicit constructor
 * @params: istream& in
 * Desription: construct a command line by reading a command-line from in, parsing it, and building instance
 * variables for argc and argv
 */
CommandLine::CommandLine(istream& in) {

	ostringstream oss;
	oss << in.rdbuf();
	string str = oss.str();
    noAmp = true;

	//cout << str << endl;
	int n = str.length();

	char char_array[n+1];
	strcpy(char_array, str.c_str());

	char *arr;
	int len;
	argc = 0;
	vector<char*> temp;

	//array that separates the char_array by spaces
	char *token = strtok(char_array, " ");
	while(token != NULL) {
		len = strlen(token);
		arr = (char *)calloc(len, sizeof(char));
		if (strcmp(token, "&") == 0) {
			noAmp = false;
		} else {
			for(int i=0; i < len; i++) {
				arr[i] = token[i];
			}
			temp.push_back(arr);
			argc++;
		}

		token = strtok(NULL, " ");

	}

	argv = new char*[temp.size()];

	for (unsigned i = 0; i < temp.size(); i++) {
			argv[i] = temp[i];
	}
}

/*
 * getCommand() method
 * @params: none
 * return a pointer to the command portion of the command line
 */
char* CommandLine::getCommand() const {
    return argv[0];
}

/*
 * getArgCount() method
 * @params: none
 * return the number of command-line arguments on the commandline
 */
int CommandLine::getArgCount() const {
    return argc;
}

/*
 * getArgVector method
 * @params: none
 * return a pointer to a char* array, each entry of which points to one 'word' of the command-line
 */
char ** CommandLine::getArgVector() const {
    return argv;
}

/*
 * getArgVector method
 * @params: int i
 * return a pointer to the ith (zero-relative) command-line 'word'
 */
char * CommandLine::getArgVector(int i) const {
    return argv[i];
}

/*
 * noAmpersand method
 * @params: none
 * return no_ampersand value
 */
bool CommandLine::noAmpersand() const {
	return noAmp;
}

/*
 * ~CommandLine()
 * Destructor for the CommandLine class
 * reclaim memory from argv to avoid leaking memory
 */
CommandLine::~CommandLine() {
	for (int i = 0; i < argc; i++) {
		delete[] argv[i];
	}
	delete[] argv;
}

