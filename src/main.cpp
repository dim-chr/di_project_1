#include <cstdlib>
#include <iostream>
#include <string>

#include "read_input.h"
#include "Configuration.h"

using namespace std;

string input_file;
string conf_file;
string out_file;
int complete;
string method;

Configuration *Configuration::instance = 0;

int main(int argc, char** argv)
{
    for(int i=0; i<argc; i++)
    {
        if(argc>2 && string(argv[i]) == "-c")
          conf_file = argv[i+1];
        
        else if(argc>2 && string(argv[i]) == "-i")
          input_file = argv[i+1];

        else if(argc>2 && string(argv[i]) == "-o")
          out_file = argv[i+1];
        
        else if(argc>2 && string(argv[i]) == "-m")
          method = argv[i+1];

        else if(argc>2 && string(argv[i]) == "-complete")
          complete = atoi(argv[i+1]);

        /*input error checking.
        if (argc < 7)
        {
            perror("Error: Too few arguments");
            exit(1);
        }
        if (argc > 7)
        {
            perror("Error: Too many arguments");
            exit(1);
        }
        */
        
    }

    // Filtrarisma grammis entolwn
    //....
    Configuration *conf = conf->getInstace();
    read_configuration("../dir/"+conf_file);

    /*
    cout << conf->number_of_clusters << endl;
    cout << conf->number_of_vector_hash_tables << endl;
    cout << conf->number_of_vector_hash_functions << endl;
    cout << conf->max_number_M_hypercube << endl;
    cout << conf->number_of_hypercube_dimensions << endl;
    cout << conf->number_of_probes << endl;
    */

    return 0;
}

