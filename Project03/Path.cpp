/** Path.cpp	Defines the implementation of the path class
*	Project03
*   Student:	Peter Haagsma
*   Date:		03/26/2019
*/

#include "Path.h"
#include <string>
#include <vector>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <dirent.h>
#include <sys/types.h>

using namespace std;

/**	Path()
*
*		This is the constructor for the path class. It creates a list of all possible
* 		paths from the path environment variable
*  		@param: none
*		return: none
*/
Path::Path() {
	char* progPath = getenv("PATH");
	char* tokenPointer;

	// Set up token pointer
	tokenPointer = strtok(progPath, ":"); 
	while (tokenPointer != NULL) {
		myDirectories.push_back(tokenPointer);
		tokenPointer = strtok(NULL, ":");
	}
}

/**	find(string program)
*
* 		This function searches myDirectories for a given program
* 		@param: string program - name of desired program
*		return: index of myDirectories containing the desired program, or -1 if the 
*				program is not found
*/
int Path::find(const string& program) const {
	int index = 0;
	if (program == ".." || program == ".") {
		index = -1;
	}
	DIR* dir;
	struct dirent* dirEnt;
	for (unsigned i = 0; i < myDirectories.size(); i++) {
		if ((dir = opendir(myDirectories[i])) != NULL) {
			while ((dirEnt = readdir(dir)) != NULL) {
				if (dirEnt->d_name == program) {
					index = i;
				}
				readdir_r(dir, dirEnt, &dirEnt);
			}
		}
		closedir(dir);
	}
	return index;
}

/** getDirectory(int i) 
*
*		This function is a getter for myDirectories, it is given an index and
*		returns the path at that index
*		@param: int index
*		return: char* path at index
*/
char* Path::getDirectory(int i) const {
	char* dir = myDirectories[i];

	return dir;
}
