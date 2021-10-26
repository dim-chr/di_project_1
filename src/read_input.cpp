#include "read_input.h"
#include "Configuration.h"
#include "Hashing.h"


void preprocessing(string filename, int L)
{
    vector<unsigned long> p;
    
    // anoigw to arxceio
    ifstream inputFile(filename);

    if (inputFile)
    {
        string line;

        // GIa kathe grammi
        while (getline(inputFile, line))
        {
            char* buff = new char[line.length()+1];
            strcpy(buff, line.c_str());
            char* token = strtok(buff," \t");

            char *id = token;

            token = strtok(buff," \t");
            // gia kathe diastasi - syntetagmeni
            while (token != NULL)
            {
                p.push_back(atoi(token));
                token = strtok (NULL, " \t");
            }

            // Gia kathe pinaka katakermatismou
            for (int i = 0; i < L; i++) {

                hashTables->insert( id, p );
            }

                        // paei ston pinaka
                        // ....

                        // adeiazw to p
            delete[] buff;
            p.clear();
        }

        inputFile.close();
    }
}

void read_configuration(string filename)
{
    Configuration *c = c->getInstace();

    ifstream infile(filename);
    int cluster_data; 

    while (infile >> cluster_data)
    {
        c->setData(cluster_data);
    }
    c->globalDataInit();
    
    
    infile.close();
}