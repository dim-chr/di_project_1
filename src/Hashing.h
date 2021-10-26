
#ifndef HASHING_H
#define HASHING_H

#include <vector>
#include <string>

using namespace std;



class HashTable
{
    private:
        int L;
        unsigned int TableSize;
        
        vector<vector<vector<string>>> hashTables;
    
    public:
    
        HashTable(int L, unsigned int TableSize);
        void insert( string id, vector<unsigned long> &p );
};


extern HashTable *hashTables;


void init_hashing(int k);

unsigned int h( const vector<unsigned long> &p );

unsigned int g( const vector<unsigned long> &p, unsigned int TableSize );



#endif /* HASHING_H */

