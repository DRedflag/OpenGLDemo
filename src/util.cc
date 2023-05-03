#include "util.h"

#include <iostream>
#include <string.h>
#include <fstream>
#include <stdio.h>

using namespace std;

bool ReadFile(const char *filename, string& outstring){
        ifstream f(filename);

        bool res = false;

        if(f.is_open()){
                string line;
                while(getline(f, line)){
                        outstring.append(line);
                        outstring.append("\n");
                }
                f.close();
                res = true;

        }
        else {
                fprintf(stderr, "Cannot open file %s\n", filename);
                exit(1);
        }
        return res;
}
