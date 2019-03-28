/***

*/

#include "Path.h"
#include "Prompt.h"
#include <iostream>

int main(int argc, char** argv) {
	Prompt p = Prompt();
	string testStr = p.get();
	cout << "\n" << testStr << endl;
}
