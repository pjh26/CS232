/*
 * SPShell.cpp
 *
 *  Created on: Mar 27, 2019
 *      Author: sjw34
 */
#include "SPShell.h"
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

using namespace std;

SPShell::SPShell() {

}

void SPShell::run() {
	Prompt pr = Prompt();
	Path pa = Path();

	while(true) {
		string input;
		cout << pr.get();
    
		//get the input from the user
		getline(cin, input);
		//prevents from a making an empty copy which throws a segmentation fault
		if (input == "") {
			continue;
		}

		istringstream aStream(input);

		CommandLine cla = CommandLine(aStream);

		//if user enters exit return from while loop
		if (strcmp(cla.getCommand(), "exit") == 0) {
			cout << "Program terminated!" << endl;
			return;
      
		//if the command was cd then change directory with chdir()
		} else if (strcmp(cla.getCommand(), "cd") == 0) {
			int return_val = chdir(cla.getArgVector(1));
			if (return_val == -1) {
				cout << return_val << endl;
				cout << "Invalid directory name..." << endl;
			} else {
				pr = Prompt();
			}
			continue;
		
    	//if command was pwd then output the working directory
		} else if (strcmp(cla.getCommand(), "pwd") == 0) {
			string pwd = pr.get();
			int pos = pwd.find("SPShell");
    		//cuts the string up until SPShell
			cout << pwd.substr(0,pos) << endl;
			continue;
		
    	// if the pa.find returns a -1 then the command cannot be found and we return 
    	// to the beginning of the loop
		} else if (pa.find(cla.getCommand()) == -1) {
			cout << "Command not found!!" << endl;
			continue;
    
    	// If none of the if statements catch then we try to run the program
		} else {
    
			pid_t pid = fork();
			// Child will see pid as 0
			if (pid == 0) {
				int index = pa.find(cla.getCommand());
				char* dir = pa.getDirectory(index);
				strcat(dir, "/");
				strcat(dir, cla.getCommand());
				char** argVec = cla.getArgVector();
				argVec[cla.getArgCount()] = NULL;

				execve(dir, argVec, environ);
        		// exit(0);
			}
			
      		// If there was no ampersand then we wait for the child to finish
			if (cla.noAmpersand() == true) {
				// Parent waits for child
				int status;
				waitpid(pid, &status, 0);
			}

		}
	}
}
