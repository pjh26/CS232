/* main.cpp	Gathers average time it takes to create a new process or thread
 * Student:	Peter Haagsma
 * Date:	02/13/2019
 */

#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/wait.h>
#include "NanoTimer.h"
#include <sys/syscall.h>

using namespace std;

/** Created threads run this function to print out their ID and exit

*/
void *PrintThreadID(void *threadid) {
	printf("Hello from the child (TID = %ld)\n", syscall(__NR_gettid));
	pthread_exit(NULL);

}

/** Main program:	takes in user arguments and outputs average time to create threads or processes
	@params: 		List of strings seperated by spaces
*/
int main(int argc, char* argv[]) {
	string str;
	bool Process = false;
	bool Thread  = false;
	int num = 1;

	// This for loop parses the list of input args and determines what the user wants
	for (int i = 1; i < (argc); i++) {
		str = argv[i];
		if (str == "-p") {
			Process = true;
		} else if (str == "-process") {
			Process = true;
		} else if (str == "-t") {
			Thread = true;
		} else if (str == "-thread") {
			Thread = true;
		} else if (str.substr(0, 2) == "-r") {
			if (str.length() > 2) {
				num = atoi(str.substr(2).c_str());
			}
			if (num < 1) {
				cout << "Please pick a valid number of repeats!!" << endl;
				return 1;
			}
		} else {
			cout << "Please enter valid commands!!" << endl;
			return 1;
		}
	}

	double processTime;
	double  threadTime;
	NanoTimer timer;

	// If the user wants to time processes
	if (Process) {
		// Then we create and time the desired number of processes
		for (int i = 0; i < num; i++) {
			timer.start();
			pid_t pid = fork();
			timer.stop();
			// In the child process, pid = 0 so only the children run these 3 lines
			if (pid == 0) {
				int id = getpid();
				printf("Hello from the child process (PID = %d)\n", id);
				exit(0);
			}
			// Parent waits for child
			wait(NULL);
		}
		//Here we calculate the average time it took and restart the timer
		processTime = (timer.getTotalTime())/(num);
		timer.reset();
	}

	// If the user wants to time threads
	if (Thread) {
		pthread_t threads[num];
		int t_int;
		// Then we create and time the desired number of threads
		for (long i = 0; i < num; i++) {
			timer.start();
			t_int = pthread_create(&threads[i], NULL, PrintThreadID, (void *)i);
			timer.stop();
			// Thread equivalent of wait
			(void) pthread_join(threads[i], NULL);
		}

		// Here we calculate the average time it took
		threadTime = (timer.getTotalTime())/(num);
	}

	// And finally output the desired information
	if (Process) printf("Average process was %f\n", processTime);
	if (Thread) printf("Average thread was %f\n", threadTime);
}

// We made it!