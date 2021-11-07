#include <cstdlib>
#include <iostream>
#include <string>

#include "read_input.h"
#include "Hashing.h"
#include "Configuration.h"

using namespace std;

Configuration *Configuration::instance = 0;

int main(int argc, char** argv)
{
    string input_file = "";
    string query_file = "";
    string out_file = "";
    int k = 4;
    int L = 5;
    int N = 1;
    int R = 10000;

    if (argc > 15)
    {
        perror("Error: Too many arguments");
        exit(1);
    }

    for(int i = 0; i < argc; i++)
    {
        
        if(argc > 2 && string(argv[i]) == "-i")
          input_file = argv[i+1];

        else if (argc > 2 && string(argv[i]) == "-q")
            query_file = argv[i+1];

        else if (argc > 2 && string(argv[i]) == "-k")
            k = atoi(argv[i+1]);

        else if (argc > 2 && string(argv[i]) == "-L")
            L = atoi(argv[i+1]);

        else if(argc > 2 && string(argv[i]) == "-o")
          out_file = argv[i+1];

        else if (argc > 2 && string(argv[i]) == "-N")
            N = atoi(argv[i+1]);

        else if (argc > 2 && string(argv[i]) == "-R")
            R = atoi(argv[i+1]);
        
    }

    if (input_file == "" || query_file == "" || out_file == "")
    {
        perror("Error: Some file names were not given");
        exit(1);
    }

    cout << "inputFile: " << input_file << endl;
    cout << "outputFile: " << out_file << endl;
    cout << "queryFile: " << query_file << endl;

    // Filtrarisma grammis entolwn
    //....
    /*conf_file = "cluster.conf";
    Configuration *conf = conf->getInstace();
    cout << "main top" << endl;
    read_configuration("../dir/"+conf_file);*/

    /*
    cout << conf->number_of_clusters << endl;
    cout << conf->number_of_vector_hash_tables << endl;
    cout << conf->number_of_vector_hash_functions << endl;
    cout << conf->max_number_M_hypercube << endl;
    cout << conf->number_of_hypercube_dimensions << endl;
    cout << conf->number_of_probes << endl;
    */

    //preprocessing(input_file, L);

	
	freeMemory();
	
    return 0;
}

