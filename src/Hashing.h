
#ifndef HASHING_H
#define HASHING_H

#include <vector>
#include <list>
#include <utility>
#include <string>

using namespace std;

class VectorData
{
    private:
    list< pair< string, vector<unsigned long> > >   vectors;
    
    public:
        pair< string, vector<unsigned long>> * insert(string id, const vector<unsigned long> &v );
        unsigned int size();
};

class HashTable
{
    private:
        int L;
        unsigned int TableSize;
        
        vector<vector<vector<pair< unsigned int, pair< string, vector<unsigned long>> * >>>> hashTables;
    
    public:
    
        HashTable(int L, unsigned int TableSize);
        void insert( int l, string id, vector<unsigned long> &p );
};


extern HashTable *hashTables;


void init_hashing(int k);

unsigned int h_func( const vector<unsigned long> &p, int i );

unsigned int g_func( const vector<unsigned long> &p, unsigned int TableSize, int i);



#endif /* HASHING_H */

