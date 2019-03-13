/** main.cpp
*
*   Student:	Peter Haagsma
*   Date:		02/26/2019
*/

#include "CMDController.h"
#include "TXTController.h"

using namespace std;

/** Main program
*
*	Takes in user arguments and outputs average time to create threads or processes
*	@params: List of strings seperated by spaces
*/
int main(int argc, char** argv) {
	
	if (argc > 1) {
		CMDController controller = CMDController(argc, argv);
		controller.run();
	} else {
		TXTController controller = TXTController();
		controller.run();
	}
}

// We made it!