#ifndef READ_INPUT_H
#define READ_INPUT_H

#include <fstream>
#include <iostream>
#include <vector>
#include <string.h>
#include <chrono>


using namespace std;

void LSH_pre_process(string filename, int L);
void Cube_pre_process(string filename, int d);

void lsh(string input, string output, int N, double R);

#endif

