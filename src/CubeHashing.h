#ifndef CUBE_HASHING_H
#define CUBE_HASHING_H

#include <vector>
#include <utility>
#include <string>

using namespace std;


// Class that contains all the hash tables that will be used, as well as the number ('L') of hash tables and the size ('TableSize') of each one
class CubeHashTable
{
    private:
        int L;  // Number of hash tables
        unsigned int TableSize;  // Number of buckets for each hash table
        
		// These are all the hash tables that will be used
		// Every bucket of each hash table contains an ID (ID(p) = r1*h1(p)+r2*h2(p)+... mod M) for the item that will be inserted
		// Each bucket also contains a pointer to a pair (item_id, vector 'p') from the list of vectors in class 'VectorData'
        
        //ToDo : Check with mike if mike should be have one less vector
        vector<vector<vector< pair<string, vector<unsigned long>> * >>> C_hashTables; 

    public:
    
        CubeHashTable(int L, unsigned int TableSize);  // Constructor
        
        
        void Cube_insert(int d, vector<unsigned long> &p, pair<string, vector<unsigned long>> * vectorPointer);  // Function that inserts an item in one of the hash tables
        vector<pair<string, double>> Cube_findNN(vector<unsigned long> &q, int N);
        vector<string> Cube_rangeSearch(vector<unsigned long> &q, double R);

};

extern CubeHashTable *C_hashTables;

void init_hashing_cube(int k, int L, int d, unsigned int TableSize);

#endif
