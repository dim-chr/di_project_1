#include "LshHashing.h"
#include "CubeHashing.h"
#include "VectorData.h"
#include "Euclidean.h"
#include "Tools.h"

#include <cstdlib>
#include <ctime>
#include <random>
#include <algorithm>
#include <cmath>
#include <map>

#define M 4294967291        // 2^32 - 5

int window;     // 'w' variable that is used by the h(p) hash functions
vector<int> r;
vector<vector<int>> g;
vector<double> t;
vector<vector<double>> v;

map<int, bool> cubeMap;

LSHHashTable *LSH_hashTables = NULL;
CubeHashTable *C_hashTables = NULL;
VectorData *vectorData;

using namespace std;

// Function that is used to initialize all the necessary variables and data structures in order to use the hash functions and the hash tables
void init_hashing_lsh(int k, int L, int d, unsigned int TableSize)
{
    // Init
    srand(time(0));
    
    window = 400; //rand() % 5 + 2;
    
    LSH_hashTables = new LSHHashTable(L, TableSize);
    vectorData = new VectorData();
    

    // Initialize the 'r' vector that will be used by every amplified hash function 'g(p)'
    {
        default_random_engine generator;
        uniform_int_distribution<int> distribution(1, 10);

        for (int i = 0; i < k; i++) {

            r.push_back(distribution(generator));
        }
    }

    // Initialize all the random 't' numbers that will be used by the hash functions 'h(p)'
    {
        default_random_engine generator;
        uniform_real_distribution<double> distribution(0, window);

        for (int i = 0; i < k; i++) {

            t.push_back(distribution(generator));
        }
    }
    
    // Initialize the all the 'v' vectors that will be used by the hash functions 'h(p)'
	// We need k vectors 'v', one for each hash function
    {
        default_random_engine generator;
        normal_distribution<double> distribution(0.0, 1.0);

        v.resize(k);

        for (int i = 0; i < k; i++) {

            for (int j = 0; j < d; j++) {
                
                v[i].push_back(distribution(generator));
            }
        }
    }

    // Initialize the 'g' vectors
	// There will be L 'g' vectors in total and each one stores the order in which the h(p) functions will be multiplied with the 'ri' numbers
	// E.g k=4, L=5, g[0]=[0,1,3,2] then g1(p)=((r1*h1(p)+r2*h2(p)+r3*h4(p)+r4*h3(p)) mod M) mod TableSize
    g.resize(L);
    for (int i = 0; i < L; i++) {
        
        for (int j = 0; j < k; j++) {
            
            int h = rand() % k;  // Get a random number from 0 to k-1

            // If this number is in the g[i] vector then keep generating new ones until one that isn't already in g[i] is found
            while(find(g[i].begin(), g[i].end(), h) != g[i].end())
            {
                h = rand() % k;
            }

            g[i].push_back(h);  // Insert that number in g[i]
        }
    }

}

// Function that is used to initialize all the necessary variables and data structures in order to use the hash functions and the hash tables
void init_hashing_cube(int k, int d, unsigned int TableSize)
{
    // Init
    srand(time(0));
    
    window = 400; //rand() % 5 + 2;
    
    C_hashTables = new CubeHashTable(1, TableSize);
    vectorData = new VectorData();

    // Initialize all the random 't' numbers that will be used by the hash functions 'h(p)'
    {
        default_random_engine generator;
        uniform_real_distribution<double> distribution(0, window);

        for (int i = 0; i < k; i++) {

            t.push_back(distribution(generator));
        }
    }
    
    // Initialize the all the 'v' vectors that will be used by the hash functions 'h(p)'
    // We need k vectors 'v', one for each hash function
    {
        default_random_engine generator;
        normal_distribution<double> distribution(0.0, 1.0);

        v.resize(k);

        for (int i = 0; i < k; i++) {

            for (int j = 0; j < d; j++) {
                
                v[i].push_back(distribution(generator));
            }
        }
    }


}

// This is the h(p) hash function
int h_func(const vector<unsigned long> &p, int i)
{
    double dot_product=0.0;
    
    // Calculate the dot product p*v
    for(int j=0; j<p.size(); j++)
    {
        dot_product += p[j] * v[i][j];
    }
    
    return (int) floor( (dot_product + t[i]) / window );
}

// This is the amplified hash function g(p)
unsigned int g_func(const vector<unsigned long> &p, unsigned int TableSize, int i)
{
    unsigned long sum=0;
    
	// Calculate the sum r1*h1(p) + r2*h2(p) +...
    for(int j=0; j<g[0].size(); j++)
    {
        sum = (sum%M) + euclidean_mod ( r[j] * h_func(p, g[i][j]) , M) ;
    }
    
    return euclidean_mod(sum , M);
}

// Constructors of HashTables class
LSHHashTable::LSHHashTable(int L, unsigned int TableSize)
{
    this->L = L;
    this->TableSize = TableSize;

    // L hash tables are needed in total
    LSH_hashTables.resize(L);

    // Each hash table hash 'TableSize' buckets
    for (int i = 0; i < L; i++) {
        LSH_hashTables[i].resize(TableSize);
    }
}

CubeHashTable::CubeHashTable(int L, unsigned int TableSize)
{
    this->L = L;
    this->TableSize = TableSize;

    // L hash tables are needed in total
    C_hashTables.resize(L);

    // Each hash table hash 'TableSize' buckets
    for (int i = 0; i < L; i++) {
        C_hashTables[i].resize(TableSize);
    }
}


// Function that inserts an item in one of the hash tables
void LSHHashTable::LSH_insert(int i, vector<unsigned long> &p, pair<string, vector<unsigned long>> * vectorPointer)
{
        // Argument 'i' needs to be smaller than 'L' because the amplified hash function gi(p), 0<= i <=L, will be called
        if(i < this->L)
        {
            unsigned int hashValue = g_func(p, this->TableSize, i);
            LSH_hashTables[i][hashValue % TableSize].push_back(make_pair(hashValue, vectorPointer));
        }
}
// Function that inserts an item in the hash table if the hypercube is used
void CubeHashTable::Cube_insert(int d, vector<unsigned long> &p, pair<string, vector<unsigned long>> * vectorPointer)
{
    unsigned int bucket = 0;
    
    // Get the result of every fi(hi(p)) function and store it in the map 'cubeMap'
	// Every different value of hi(p) corresponds to 0 or 1 in the map
    for (int i = 0; i < d; i++) {
        
		// Get hi(p)
        int hi = h_func(p, i);
        
        // If there is no key value in the map that is equal to hi(p) then hi(p) is inserted and is given a mapped value of 0 or 1 randomly
        if(cubeMap.find(hi) == cubeMap.end())
            cubeMap[hi] = rand() % 2;
        
		// Perform bitwise operations to concatenate all the bits that we will get from this loop
        bucket |= cubeMap[hi];
        bucket <<= 1;
    }
	
	// Insert the item in the correct bucket
    C_hashTables[0][bucket].push_back(vectorPointer);
}


// Function that finds the N approximate nearest neighbors for LSH
vector<pair<string, double>> LSHHashTable::LSH_findNN(vector<unsigned long> &q, int N)
{
    vector<pair<string, double>> b;
    
    // For each hash table
    for (int i = 0; i < L; i++) {
        
		// Get the bucket that query 'q' belongs in
        unsigned int hashValue = g_func(q, this->TableSize, i);
        
        // For each item in the bucket
        for(auto candidate : LSH_hashTables[i][hashValue % TableSize])
        {
            string id = candidate.second->first;  // Get the 'item_id' of the point
            vector<unsigned long> &p = candidate.second->second;  // Get the coordinates of the point
            
            b.push_back(make_pair(id , euclidean_distance(p, q)));  // Make the 'item_id' and the coordiantes a pair and insert it in the vector 'b'
        }
    }
    
    // Sort the vector 'b' to find the shortest distances
    sort(b.begin(), b.end(), sortbyDist);
    
    // Only keep the N shortest distances
    if(b.size() > N){
        b.resize(N);
    }
    
    return b;
}

vector<pair<string, double>> CubeHashTable::Cube_findNN(vector<unsigned long> &q, int N)
{
    vector<pair<string, double>> b; 
    return b;
}
// Function that finds all the points within a certain radius 'R' of query 'q'
vector<string> LSHHashTable::LSH_rangeSearch(vector<unsigned long> &q, double R)
{
    vector<string> b;
    
    // For each hash table
    for (int i = 0; i < L; i++) {
        
		// Get the bucket that query 'q' belongs in
        unsigned int hashValue = g_func(q, this->TableSize, i);
        
        // For each item in the bucket
        for(auto candidate : LSH_hashTables[i][hashValue % TableSize])
        {
            string id = candidate.second->first;  // Get the 'item_id' of the point
            vector<unsigned long> &p = candidate.second->second;  // Get the coordinates of the point
            
			// If the euclidean distance of 'p' from 'q' is smaller than radius 'R' then 'p' is within that radius
			// Then the 'item_id' of 'p' is inserted in the vector 'b'
            if(euclidean_distance(p, q) < R)
            {
                b.push_back(id);
            }
        }
    }
    
    return b;
}

vector<string> CubeHashTable::Cube_rangeSearch(vector<unsigned long> &q, double R)
{
    vector<string> b; 
    return b;
}

void DeallocateMemory()
{
	delete vectorData;
    
    if (LSH_hashTables != NULL)
	    delete LSH_hashTables;
    if (C_hashTables != NULL)
        delete C_hashTables;
}
