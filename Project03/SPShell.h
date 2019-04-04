/*
 * SPShell.h
 *
 *  Created on: Mar 27, 2019
 *      Author: sjw34
 */

#ifndef SPSHELL_H_
#define SPSHELL_H_


#include <stdio.h>
#include <iostream>
#include <vector>
#include <string.h>
#include <stdlib.h>
#include <sstream>
#include "Path.h"
#include "Prompt.h"
#include "CommandLine.h"

class SPShell {
public:
	SPShell();
	void run();
};



#endif /* SPSHELL_H_ */
