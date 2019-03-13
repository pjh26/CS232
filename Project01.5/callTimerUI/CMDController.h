/** CMDController.h - Used to control the CMDinterface class as well act as a bridge between 
*					  the interface and the model
*
*   Student:	Peter Haagsma
*   Date:		02/26/2019
*/

#ifndef CMD_CONTROLLER_H_
#define CMD_CONTROLLER_H_

#include "CMDInterface.h"
#include "CallTimer.h"

using namespace std;

class CMDController {
public:
	CMDController(int argc, char** argv);
	void run();

private:
	void parseCommand(bool &process, bool &thread, int &numRep);
	void runCallTimer(bool process, bool thread, int numRep);

	int 	ARG_C;
	char**	ARG_V;
	CMDInterface CMD = CMDInterface();
};

/** CMDController(int argc, char** argv)
*	
*	This is the constructor for the CMDController class, it is used to define a couple of variables
*	@params: int argc (how many inputs there are) and an array of char* containing the commandline inputs
*/
CMDController::CMDController(int argc, char** argv) {
	ARG_C = argc;
	ARG_V = argv;
}

/** run()
*
*	This function could be inside the constructor however, separating the constructor
*	and the run function allows the person who called the class to create the controller
*	object whenever they want and run it whenever they want.
*/
void CMDController::run() {
	bool process;				// Process, thread and numRep vars are initialized here because they
	bool thread;				// will be passed by reference to our parseCommand function
	int numRep;
	parseCommand(process, thread, numRep); 

	string confirmation = CMD.confirm(process, thread, numRep);
	if ( !(confirmation == "Y" || confirmation == "y") )  {
		CMD.quit();
	}

	runCallTimer(process, thread, numRep);

	CMD.quit();
}

/** parseCommand(bool &process, bool &thread, int &numRep)
*
*	This command takes the arguments from the command line and sets the process, thread,
*	and numRep variables accordingly
*	@params: process, thread, numRep. These are passed by reference so that global variables
*			 could be avoided.
*/
void CMDController::parseCommand(bool &process, bool &thread, int &numRep) {
	process = false;	// Set the variables to default values
	thread = false;		// numRep defaults to 1 because if the user doesn't have a -rXX term
	numRep = 1;			// then the command should default to one repetition.
	string str;

	// This for loop parses the list of input args and determines what the user wants
	for (int i = 1; i < (ARG_C); i++) {
		str = ARG_V[i];
		if (str == "-p" || str == "-process") {
			process = true;
		} else if (str == "-t" || str == "-thread") {
			thread = true;
		} else if (str.substr(0, 2) == "-r") {
			if (str.length() > 2) {
				try {		// If the user enters a valid -r term then it is passed to numRep
					numRep = atoi(str.substr(2).c_str());
				} catch (exception &e) { // If the user enters a bad -r term a 0 is passed to numRep
					numRep = 0;
				}
			}
		} else {
			CMD.error();
		}
	}

	if (!process && !thread) { 	// if the user only puts in an -rXX term then we throw an error
		CMD.error();
	}

	if (numRep < 1) {			// If the user puts a bad -rXX term then we throw an error
		CMD.error();
	}
}

/** runCallTimer(bool process, bool thread, int numRep)
*
*	This function interprets the users choices and sends them to the model to get desired info
*	then relays that to the interface to be displayed
*	@params: bool process & thread, and the desired number of repetitions, these will
*			 be used to determine how the CallTimer model is modeled
*/
void CMDController::runCallTimer(bool process, bool thread, int numRep) {
	double pTime = 0;
	double tTime = 0;
	
	CallTimer Ctmr = CallTimer(process, thread, numRep); // Call the model

	if (process) pTime = Ctmr.getProcessTime(); // get the times, we use ifs to avoid unnecessary function calls
	if (thread)  tTime = Ctmr.getThreadTime();  // it would achieve the same goal without them but it saves some time

	CMD.displayResults(pTime, tTime); // We send those results to the interface to be displayed
}

#endif /* CMD_CONTROLLER_H_ */