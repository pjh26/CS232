/** Prompt.cpp	Defines the implementation of the path class
*	Project03
*   Student:	Peter Haagsma
*   Date:		03/26/2019
*/

#include <unistd.h>
#include <limits.h>
#include "Prompt.h"

using namespace std;

/**	Prompt()
*
*		This is the constructor for the prompt class. it gets the current working directory
*		and customizes it to look nice
*		@param: none
*		return: none
*/
Prompt::Prompt() {
	curDir = getcwd(buff, PATH_MAX + 1);
	curDir = curDir + "/SPShell$ ";
}

/**	get()
*
*		This function simply returns the current working directory as a string
*		@param: none
*		return: string current Directory
*/
string Prompt::get() const {
	return curDir;
}
