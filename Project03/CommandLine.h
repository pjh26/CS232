//
//  CommandLine.hpp
//  project03
//
//  Created by Sameer Mall on 3/19/19.
//  Copyright © 2019 Sameer Mall. All rights reserved.
//

#ifndef CommandLine_h
#define CommandLine_h

#include <stdio.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <sstream>
#include <vector>

using namespace std;
class CommandLine {

// Methods
public:
    CommandLine();
    CommandLine(istream& in);
    char* getCommand() const;
    int getArgCount() const;
    char ** getArgVector() const;
    char * getArgVector(int i) const;
    bool noAmpersand() const;
    ~CommandLine();

// Instance variables
private:
    int argc;
    bool noAmp;
    char** argv;
};


#endif /* CommandLine_h */

