
#ifndef CONFIGURATION_H
#define CONFIGURATION_H

/*
Configuration class follows a Singleton pattern structure
Ussing this pattern we can have multiple instances of the same object.
*/
class Configuration 
{
    static Configuration *instance;
    
    /*
    We will save all the configuration inside a private vector.
    */
    std::vector<int> data;

    Configuration()
    {
        number_of_clusters = 0;
        number_of_vector_hash_tables = 0;
        number_of_vector_hash_functions = 0;
        max_number_M_hypercube = 0;
        number_of_hypercube_dimensions = 0;
        number_of_probes = 0;
    }

    public:

    int number_of_clusters;
    int number_of_vector_hash_tables;
    int number_of_vector_hash_functions;
    int max_number_M_hypercube;
    int number_of_hypercube_dimensions;
    int number_of_probes;

    static Configuration *getInstace()
    {
        if(!instance)
            instance = new Configuration();
        return instance;
    }

    std::vector<int> getData()
    {
        return this->data;
    }
    void setData(int _data)
    {
        this->data.push_back(_data);
    }
    void globalDataInit()
    {
        number_of_clusters = data[0];
        number_of_vector_hash_tables = data[1];
        number_of_vector_hash_functions = data[2];
        max_number_M_hypercube = data[3];
        number_of_hypercube_dimensions = data[4];
        number_of_probes = data[5];
    }
};

#endif