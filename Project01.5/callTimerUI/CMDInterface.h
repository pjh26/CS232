/** CMDInterface.h - This subclass inherits from Interface and interacts with the user. It relays 
*					 the user inputs to the CMDcontoller class as well as display the data collected
*					 by the controller
*
*   Student:	Peter Haagsma
*   Date:		02/26/2019
*/

#ifndef CMD_INTERFACE_H_
#define CMD_INTERFACE_H_

#include "Interface.h"

using namespace std;

class CMDInterface: public Interface {
public:
	string confirm(bool process, bool thread, int numRep);
	void error();
};

/** confirm(bool process, bool thread, int numRep)
*
*	This function gives the user a chance to see how the program interpreted their input, allowing
* 	them to make sure that what they want to happen is actually happening
*	@param: bool process, thread, int numRep. The booleans are used to determine what the messge will
*			say and the numRep is changed to a string to include in the message
*	return: Returns the user input (string)
*/
string CMDInterface::confirm(bool process, bool thread, int numRep) {
	string choiceSTR, numSTR;

	if (process && thread) {	// We check the case of process && thread first to get the correct method
		choiceSTR = "how long it takes to create both threads and processes";
	} else if (process) {
		choiceSTR = "how long it takes to create a process";
	} else if (thread) {
		choiceSTR = "how long it takes to create a thread";
	}

	ostringstream stm;		// These three lines are used to convert the int numRep into a string for 
	stm << numRep;			// outputting to the console
    numSTR = stm.str() ;

	cout << "\nYou have decided to time " + choiceSTR + " for " + numSTR + " repetitions.\n" << endl;
	cout << "Would you like to continue? (Y/N)\n";

	cin >> USER_INPUT;		// Here we return the user input
	cout << endl;
	return USER_INPUT;
}

/** error()
*
*	This simply overrides the super definition of error. It adds a line after the message
*	and exits the program.
*/
void CMDInterface::error() {
	Interface::error();
	cout << endl;
	exit(1);
}

#endif /* CMD_INTERFACE_H_ */