#include "read_input.h"
#include "Configuration.h"

void preprocessing(string filename)
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
			char* token = strtok(line.c_str()," ");
			
			// gia kathe diastasi - syntetagmeni
            while (token != NULL)
            {
				p.push_back(atoi(token));
                token = strtok (NULL, " ");
            }
			
			// paei ston pinaka
			// ....
			
			// adeiazw to p
			p.clear();
		}
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
}