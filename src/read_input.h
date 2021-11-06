#ifndef READ_INPUT_H
#define READ_INPUT_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <string.h>
#include "Configuration.h"

using namespace std;

void preprocessing(string , int );
void read_configuration(string filename);
int extractIntegerFromString(string str);
void read_queries(string input, string output, int N, double R);

#endif

