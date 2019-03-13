/** TXTController.h	- Used to control the TXTinterface class as well act as a bridge between 
*					  the interface and the model
*
*   Student:	Peter Haagsma
*   Date:		02/26/2019
*/

#ifndef TXT_CONTROLLER_H_
#define TXT_CONTROLLER_H_

#include "TXTInterface.h"
#include "CallTimer.h"

using namespace std;

class TXTController {
public:
	void run();
private:
	int runOptionLoop();
	int runNumberLoop(int userChoice);
	void runCallTimer(int userChoice, int numRepetitions);

	TXTInterface TXT = TXTInterface();
};


/** run()
*
*	This function could be inside the constructor however, separating the constructor
*	and the run function allows the person who called the class to create the controller
*	object whenever they want and run it whenever they want.
*/
void TXTController::run() {
	int userChoice;
	int numRepetitions;

	// This loop allows user to use the program as long as they want. It is terminated by the
	// user entering an exit command
	while (true) {
		userChoice = runOptionLoop(); // displays options duh

		numRepetitions = runNumberLoop(userChoice); // allows user to pick number of repetitions

		runCallTimer(userChoice, numRepetitions); // runs our model

		TXT.pause(); // wait for user to be ready to continue
	}
}

/** runOptionLoop()
*
*	This function loops until the user enters a valid option
*	returns: The option (int) the user selected or exits the program if the user selects quit
*/
int TXTController::runOptionLoop() {
	int optionNUM;
	string optionSTR;
	while (true) {
		optionSTR = TXT.PTOption();

		try {									// If the user enters a number then it is passed to optionNUM
			optionNUM = atoi(optionSTR.c_str());
		} catch (exception &e) {				// If the user enters anything else a 0 is passed to optionNUM
			optionNUM = 0;
		}

		switch (optionNUM) {		// If the number is 1-3 its returned, 4 means we exit otherwise error
			case 1:
				return optionNUM;
			case 2:
				return optionNUM;
			case 3:
				return optionNUM;
			case 4:
				TXT.quit();
			default:
				TXT.error();
		}
	}
}

/** runNumberLoop(userChoice)
*
*	This function loops until the user picks a valid number of repetitions
*	@params: int containing the userChoice, this is sent to the interface to help the 
*			 UI be more informative
* 	returns: the number of repetitions the user wants
*/
int TXTController::runNumberLoop(int userChoice) {
	int numRepetitions;
	string numSTR;
	while (true) {
		
		numSTR = TXT.NUMOption(userChoice); // Sends userChoice to the interface 

		try {									// If the user enters a number then it is passed to numRep
			numRepetitions = atoi(numSTR.c_str());
		} catch (exception &e) {				// If the user enters anything else a 0 is passed to numRep
			numRepetitions = 0;
		}

		if (numRepetitions < 1)  {
			TXT.error(); // If it isn't valid (less than 1) then we tell the interface to error
		} else {
			return numRepetitions; // Otherwise we return the value
		}
	}
}

/** runCallTimer(userChoice, numRepetitions)
*
*	This function interprets the users choices and sends them to the model to get desired info
*	then relays that to the interface to be displayed
*	@params: int containing the user choice, and the desired number of repetitions, these will
*			 be used to determine how the CallTimer model is modeled
*/
void TXTController::runCallTimer(int userChoice, int numRepetitions) {
	bool thread = false;
	bool process = false;

	double pTime = 0;
	double tTime = 0;

	// Here we take the users choice and translate it for the model to use
	switch (userChoice) {
		case 1:
			thread = true;
			break;
		case 2:
			process = true;
			break;
		case 3:
			thread = process = true;
			break;
	}

	CallTimer Ctmr = CallTimer(process, thread, numRepetitions); // Call the model

	if (process) pTime = Ctmr.getProcessTime(); // get the times, we use ifs to avoid unnecessary function calls
	if (thread)  tTime = Ctmr.getThreadTime();  // it would achieve the same goal without them but it saves some time

	TXT.displayResults(pTime, tTime); // We send those results to the interface to be displayed
}

#endif /* TXT_CONTROLLER_H_ */