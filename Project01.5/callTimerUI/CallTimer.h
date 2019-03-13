/** CallTimer.h - This class times how long it takes to create a new process or thread
*	
*   Student:	Peter Haagsma
*   Date:		02/26/2019
*/

#ifndef CALL_TIMER_H_
#define CALL_TIMER_H_

#include "NanoTimer.h"
#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/wait.h>
#include <sys/syscall.h>

using namespace std;

class CallTimer {
public:
	CallTimer( bool Process, bool Thread, int num);
	double getProcessTime()	{ return processTime; }
	double getThreadTime()	{ return threadTime; }
private:
	double processTime = 0;
	double threadTime = 0;
	void process(int num);
	void thread(int num);
	void *PrintThreadID(void *threadid);
	
	class ThreadTask {
	public:
		void *PrintThreadID(void *threadid);
	};
};

CallTimer::CallTimer( bool Process, bool Thread, int num) {
	if (Process) process(num);
	if (Thread) thread(num);
}

void* CallTimer::ThreadTask::PrintThreadID(void* threadid) {
	printf("Hello from the child (TID = %ld)\n", syscall(__NR_gettid));
	pthread_exit(NULL);
}

void CallTimer::process(int num) {
	NanoTimer timer;
	// We create and time the desired number of processes
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
}

void CallTimer::thread(int num) {
	NanoTimer timer;
	pthread_t threads[num];
	ThreadTask *taskPtr = new ThreadTask();
	// Then we create and time the desired number of threads
	for (long i = 0; i < num; i++) {
		timer.start();
		// Yeah... I have no clue whats going on with the void stars, but it worked. Heres the link
		// https://stackoverflow.com/questions/1151582/pthread-function-from-a-class
		(void) pthread_create(&threads[i], NULL, (void* (*)(void*)) &ThreadTask::PrintThreadID, taskPtr); 
		timer.stop();
		// Thread equivalent of wait
		pthread_join(threads[i], NULL);
	}
	// Here we calculate the average time it took
	threadTime = (timer.getTotalTime())/(num);
}



#endif /* NANO_TIMER_H_ */

