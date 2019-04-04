/** Prompt.h
*	Project03
*   Student:	Peter Haagsma
*   Date:		03/26/2019
*/

#ifndef PROMPT_H_
#define PROMPT_H_

#include <string>

class Prompt {
public:
	Prompt();
	std::string get() const;
private:
	std::string curDir;
	char buff[PATH_MAX];
};

#endif /* PROMPT_H_ */