#include "read_input.h"
#include "Configuration.h"

void preprocessing(string filename)
{
    vector<unsigned long> p;
    
    // anoigw to arxceio
    
    // GIa kathe grammi
    {
        // gia kathe diastasi - syntetagmeni
        {
            p.push_back( 78 );
        }
        
        // paei ston pinaka
        // ....
        
        // adeiazw to p
        p.clear();
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