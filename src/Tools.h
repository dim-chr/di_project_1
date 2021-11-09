#ifndef TOOLS_H
#define TOOLS_H

#include <utility>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

bool sortbyDist(const pair<string, double> &a, const pair<string, double> &b);

void DeallocateMemory();

//void read_configuration(string filename);
//int extractIntegerFromString(string str);
int dimension(string filename);
int count_file_lines(string filename);

/* h and g functions for LSH and hypercube calculations */
int h_func(const vector<unsigned long> &p, int i);
unsigned int g_func(const vector<unsigned long> &p, unsigned int TableSize, int i);

#endif