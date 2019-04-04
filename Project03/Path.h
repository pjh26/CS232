/** Path.h
*	Project03
*   Student:	Peter Haagsma
*   Date:		03/26/2019
*/

#ifndef PATH_H_
#define PATH_H_

#include <string>
#include <vector>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <dirent.h>
#include <sys/types.h>

class Path {
public:
	Path();
	int find(const std::string& program) const;
	char* getDirectory(int i) const;
private:
	std::vector<char*> myDirectories;
};

#endif /* PATH_H_ */