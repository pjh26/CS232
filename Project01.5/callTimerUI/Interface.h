/** Interface.h - This class interacts with the user and relays the user inputs to the
*				  contoller class as well as display the data collected by controller
*
*   Student:	Peter Haagsma
*   Date:		02/26/2019
*/

#ifndef INTERFACE_H_
#define INTERFACE_H_

#include <iostream>
#include <string>
#include <cstdlib>
#include <exception>
#include <stdio.h>
#include <sstream>

using namespace std;

class Interface {
public:
	void displayResults(double pTime, double tTime);
	void pause();
	void error();
	void quit();
protected:
	string USER_INPUT;

};

/** displayResults(processTime, threadTime)
*
*	This function simply takes the average times given from the controller and displays them nicely
*	It only displays the time if it has been changed from 0
*	@params: the average process and thread time, if one is equal to zero then it will not be displayed
*/
void Interface::displayResults(double pTime, double tTime) {
	if ( pTime > 0 ) printf("\nAverage process was %f\n", pTime);
	if ( tTime > 0 ) printf("\nAverage thread was %f\n", tTime);
}

/** quit()
*
*	Displays a nice menu then exits the program with a successful "0" code
*/
void Interface::quit() {
	cout << "\nThank you for using the thread and process timing machine. Have a great day!\n\n\n";
	exit(0);
}

/** error()
*
* 	Informs the user that they have entered something incorrectly
*/
void Interface::error() {
	cout << "\nPlease enter a valid input!" << endl;
}

/** pause()
*
*	Uses cin to pause the program so the current screen does not move away and allows the user
* 	to progress at their own pace
*/
void Interface::pause() {
	cout << "\nEnter any letter when ready to continue." << endl;
	cin >> USER_INPUT;
}

#endif /* INTERFACE_H_ */