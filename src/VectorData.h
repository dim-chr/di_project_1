#ifndef VECTOR_H
#define VECTOR_H

#include <list>
#include <vector>
#include <utility>
#include <string>

using namespace std;

// Class that is used to store all the vectors 'p' from the input file
class VectorData
{
    private:

    list<pair<string, vector<unsigned long>>> vectors;  // Each node of this list contains the 'item_id' of each vector 'p' and its coordinates
    
    public:
        pair<string, vector<unsigned long>> * insert(string id, const vector<unsigned long> &v );  // Function that is used to insert each vector in the list
        unsigned int size();  // Function that returns the size of the list
        vector<double> findRealDistBruteForce(vector<unsigned long> &q, int N);
};

extern VectorData *vectorData;

#endif