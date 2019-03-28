/** Prompt.h
*	
*   Student:	Peter Haagsma
*   Date:		03/26/2019
*/

#ifndef PROMPT_H_
#define PROMPT_H_

#include <unistd.h>
#include <limits.h>
#include <string>

using namespace std;

class Prompt {
public:
	Prompt();
	string get() const;
private:
	string curDir;
	char buff[PATH_MAX];
};

Prompt::Prompt() {
	curDir = getcwd(buff, PATH_MAX + 1);
	curDir = curDir + "/SPShell$ ";
}

string Prompt::get() const {
	return curDir;
}

#endif /* PROMPT_H_ */