#define _CRT_SECURE_NO_WARNINGS
#include <cstdlib>
#include <iostream>
#include <string>
#include <cmath>

#include "Methods.h"
#include "Tools.h"
#include "CubeHashing.h"

using namespace std;

int main(int argc, char** argv)
{
    string input_file = "";
    string query_file = "";
    string out_file = "";
    int k = 10;
    int M = 50;
    int probes = 15;
    int N = 3;
    int R = 10000;

    if (argc > 17)
    {
        cout << "Error: Too many arguments" << endl;
        exit(1);
    }

    for (int i = 0; i < argc; i++)
    {

        if (string(argv[i]) == "-i")
            input_file = argv[i + 1];

        else if (string(argv[i]) == "-q")
            query_file = argv[i + 1];

        else if (string(argv[i]) == "-k")
            k = atoi(argv[i + 1]);

        else if (string(argv[i]) == "-M")
            M = atoi(argv[i + 1]);

        else if (string(argv[i]) == "-probes")
            probes = atoi(argv[i + 1]);

        else if (string(argv[i]) == "-o")
            out_file = argv[i + 1];

        else if (string(argv[i]) == "-N")
            N = atoi(argv[i + 1]);

        else if (string(argv[i]) == "-R")
            R = atoi(argv[i + 1]);

    }

    if (input_file == "" || query_file == "" || out_file == "")
    {
        cout << "Error: Some file names were not given" << endl;
        exit(1);
    }

    cout << "inputFile: " << input_file << endl;
    cout << "outputFile: " << out_file << endl;
    cout << "queryFile: " << query_file << endl;
    cout << "dimension: " << dimension(input_file) << endl;
    cout << "File lines: " << count_file_lines(input_file) << endl;

    init_hashing_cube(k, dimension(input_file), pow(2, k));

    Cube_pre_process(input_file, k);
    
    cube(query_file, out_file, N, k, R, M, probes);

    DeallocateMemory();

    return 0;
}