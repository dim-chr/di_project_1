#include <cstdlib>
#include <iostream>
#include <string>

#include "Methods.h"
#include "Tools.h"
#include "LshHashing.h"

using namespace std;

int main(int argc, char** argv)
{
    string input_file = "";
    string query_file = "";
    string out_file = "";
    int k = 4;
    int L = 5;
    int N = 5;
    int R = 10000;

    if (argc > 15)
    {
        perror("Error: Too many arguments");
        exit(1);
    }

    for(int i = 0; i < argc; i++)
    {
        
        if(string(argv[i]) == "-i")
          input_file = argv[i+1];

        else if (string(argv[i]) == "-q")
            query_file = argv[i+1];

        else if (string(argv[i]) == "-k")
            k = atoi(argv[i+1]);

        else if (string(argv[i]) == "-L")
            L = atoi(argv[i+1]);

        else if(string(argv[i]) == "-o")
          out_file = argv[i+1];

        else if (string(argv[i]) == "-N")
            N = atoi(argv[i+1]);

        else if (string(argv[i]) == "-R")
            R = atoi(argv[i+1]);
        
    }

    if (input_file == "" || query_file == "" || out_file == "")
    {
        cout << "Error: Some file names were not given" << endl;
        exit(1);
    }

    cout << "Reading from: " << input_file << endl;
    cout << "Writing in: " << out_file << endl;
    cout << "Getting querries from: " << query_file << endl;

    init_hashing_lsh(k, L, dimension(input_file), count_file_lines(input_file) / 8);
    
    LSH_pre_process(input_file, L);

    lsh(query_file, out_file, N, R);

    DeallocateMemory();
	
    return 0;
}

