#ifndef CUBE_HASHING_H
#define CUBE_HASHING_H

#include <vector>
#include <utility>
#include <string>

#include <fstream>

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
        
        
        vector<vector<vector< pair<string, vector<unsigned long>> * >>> C_hashTables; 

    public:
    
        CubeHashTable(int L, unsigned int TableSize);  // Constructor
        
        
        void Cube_insert(vector<unsigned long> &p, pair<string, vector<unsigned long>> * vectorPointer, int k);  // Function that inserts an item in one of the hash tables
        vector<pair<string, double>> Cube_findNN(vector<unsigned long> &q, int N, int k, int maxPoints, int probes);
        vector<string> Cube_rangeSearch(vector<unsigned long> &q, int k, double R, int maxPoints, int probes);

        
        void printHash( )
        {
            ofstream out("ids.txt");

            for (int i = 0; i < L; i++)
            {
                out << "HashTable " << i << endl;
                for (int j = 0; j < TableSize; j++)
                {
                    out << "Bucket " << j;
                    for (int k = 0; k < C_hashTables[i][j].size(); k++)
                    {
                        out << " | Item_id: " << C_hashTables[i][j][k]->first;
                    }
                    out << endl;
                }
                out << "\n\n";
            }

            out.close();
        }
};

extern CubeHashTable *C_hashTables;

void init_hashing_cube(int k, int d, unsigned int TableSize);

#endif
