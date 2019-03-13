/** TXTInterface.h - This subclass inherits from Interface and interacts with the user. It relays 
*					 the user inputs to the TXTcontoller class as well as display the data collected
*					 by the controller
*					 
*   Student:	Peter Haagsma
*   Date:		02/26/2019
*/

#ifndef TXT_INTERFACE_H_
#define TXT_INTERFACE_H_

#include "Interface.h"

using namespace std;

class TXTInterface: public Interface {
public:
	TXTInterface();
	string PTOption();
	string NUMOption(int PTOption);
};

/** TXTInterface() 
*
*	Constructor simply displays some intro text to the user
*/
TXTInterface::TXTInterface() {
	cout << "\n\n\nWelcome to the thread and process timing machine!! Time your processes and threads right here!\n\nTime 10 threads today and get the eleventh free!\n\nIn fact, if you time 10 threads and processes within the hour\n\nI'll include 50, thats right you heard it, 50 threads AND processes for FREE! \n\n";
	cout << "\n\n\nPlease select whether you want to time processes or threads in the following menu" << endl;
}

/** PTOption()
*
*	This function displays the menu and takes in the user choice
*	returns: An integer based on the user input, and 0 if the input isn't a number
*/
string TXTInterface::PTOption() {
	cout << "\nPlease enter the corresponding number of your choice\n" << endl;
	cout << "1: . . Threads" << endl;
	cout << "2: . . Processes" << endl;
	cout << "3: . . Threads and Processes" << endl;
	cout << "4: . . Exit" << endl;
	
	cin >> USER_INPUT;
	return USER_INPUT;
}

/** NUMOption(Process/Thread Option)
*
*	This function recieves the (int) users choice and then asks for how may repetitions.
*	Depending on the choice it displays a different question for the users sake
*	@params: an integer from 1-3, this is used to 'personalize' the question
*	returns: the user input
*/
string TXTInterface::NUMOption(int PTOption) {
	string strOption;
	switch (PTOption) {
		case 1:
			strOption = "Threads";
			break;
		case 2:
			strOption = "Processes";
			break;
		case 3:
			strOption = "Threads & Processes";
			break;
	}

	cout << "\nHow many " + strOption + " would you like to time?" << endl;
	cout << "Please enter a whole number greater than zero" << endl;
	
	cin >> USER_INPUT;
	return USER_INPUT;
}

#endif /* TXT_INTERFACE_H_ */