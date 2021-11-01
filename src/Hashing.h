
#ifndef HASHING_H
#define HASHING_H

#include <vector>
#include <list>
#include <utility>
#include <string>

using namespace std;

// Class that is used to store all the vectors 'p' from the input file
class VectorData
{
    private:
    list< pair<string, vector<unsigned long>> >   vectors;  // Each node of this list contains the 'item_id' of each vector 'p' and its coordinates
    
    public:
        pair<string, vector<unsigned long>> * insert(string id, const vector<unsigned long> &v );  // Function that is used to insert each vector in the list
        unsigned int size();  // Function that returns the size of the list
};

// Class that contains all the hash tables that will be used, as well as the number ('L') of hash tables and the size ('TableSize') of each one
class HashTable
{
    private:
        int L;  // Number of hash tables
        unsigned int TableSize;  // Number of buckets for each hash table
        
		// These are all the hash tables that will be used
		// Every bucket of each hash table contains an ID (ID(p) = r1*h1(p)+r2*h2(p)+... mod M) for the item that will be inserted
		// Each bucket also contains a pointer to a pair (item_id, vector 'p') from the list of vectors in class 'VectorData'
        vector<vector<vector< pair< unsigned int, pair<string, vector<unsigned long>> * >>>> hashTables;
    
    public:
    
        HashTable(int L, unsigned int TableSize);  // Constructor
        void insert(int l, string id, vector<unsigned long> &p);  // Function that inserts an item in the hash table
};


extern HashTable *hashTables;


void init_hashing(int k);

unsigned int h_func(const vector<unsigned long> &p, int i);

unsigned int g_func(const vector<unsigned long> &p, unsigned int TableSize, int i);



#endif

