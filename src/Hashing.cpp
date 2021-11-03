
#include "Hashing.h"
#include "Euclidean.h"

#include <cstdlib>
#include <ctime>
#include <random>
#include <algorithm>
#include <cmath>

/*
 * 
 * 
 * 
 * TODO: Svinoume to vectorData pou egine me new
 * TODO: Svinoume to hashTbales pou egine me new
 * */

#define M 4294967291        // 2^32 - 5

int window;     // 'w' variable that is used by the h(p) hash functions
vector<int> r;
vector<vector<int>> g;
vector<double> t;
vector<vector<double>> v;

HashTable *hashTables;
VectorData *vectorData;

using namespace std;

// Function that is used to initialize all the necessary variables and data structures in order to use the hash functions and the hash tables
void init_hashing(int k, int L, int d, unsigned int TableSize)
{
    // Init
    srand(time(0));
    
    window = 400; //rand() % 5 + 2;
    
    hashTables = new HashTable(L, TableSize);
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


// This is the h(p) hash function
unsigned int h_func(const vector<unsigned long> &p, int i)

{
    
    double dot_product=0.0;
    
    // Calculate the dot product p*v
    for(int j=0; j<p.size(); j++)
    {
        dot_product += p[j] * v[i][j];
    }
    
    return (unsigned int) floor((dot_product + t[i]) / window);
}

// This is the amplified hash function g(p)
unsigned int g_func(const vector<unsigned long> &p, unsigned int TableSize, int i)
{
    unsigned long sum=0;
    
	// Calculate the sum r1*h1(p) + r2*h2(p) +...
    for(int j=0; j<g[0].size(); j++)
    {
        sum += r[j] * h_func(p, g[i][j]);
    }
    
    return (unsigned int) (sum % M);
}


/*======================================================*/


// Function that is used to insert each vector in the list
pair<string, vector<unsigned long>> * VectorData::insert(string id, const vector<unsigned long> &v)
{
    vectors.push_back(make_pair(id, v));  // Insert the 'item_id' of vector 'p' and its coordinates
    
    // Get the item that was just inserted in the list
    pair< string, vector<unsigned long>>& p = vectors.back();
    
    // Return the item's address
    return &p;
}

// Function that returns the size of the list
unsigned int VectorData::size()
{
    return vectors.size();
}

// Function that finds the real distances between query point 'q' and its N nearest neighbors using exhaustive search
vector<double> VectorData::findRealDistBruteForce( vector<unsigned long> &q, int N )
{
    vector<double> b;
    
    // For every point 'p' calculate its distance from 'q'
    for(auto candidate : vectors)
    {
        vector<unsigned long> &p = candidate.second;
        b.push_back(euclidean_distance(p, q));
    }
    
	// Sort the vector 'b' to find the shortest distances
    sort(b.begin(), b.end());
    
	// Only keep the N shortest distances
    b.resize(N);
    
    return b;
}

void VectorData::deleteData()
{
    delete vectorData;
}

/*=======================================================*/

// Constructor of HashTable class
HashTable::HashTable(int L, unsigned int TableSize)
{
    this->L = L;
    this->TableSize = TableSize;

    // L hash tables are needed in total
    hashTables.resize(L);

    // Each hash table hash 'TableSize' buckets
    for (int i = 0; i < L; i++) {
        hashTables[i].resize(TableSize);
    }
}

// Function that inserts an item in one of the hash tables
void HashTable::insert(int i, vector<unsigned long> &p, pair<string, vector<unsigned long>> * vectorPointer)
{
    // Argument 'i' needs to be smaller than 'L' because the amplified hash function gi(p), 0<= i <=L, will be called
    if(i < this->L)
    {
        unsigned int hashValue = g_func(p, this->TableSize, i);
        hashTables[i][hashValue % TableSize].push_back(make_pair(hashValue, vectorPointer));
    }
}

// Function that is given as an argument to the 'sort' function in order to sort a vector that contains pairs
bool sortbyDist(const pair<string, double> &a, const pair<string, double> &b)
{
    return a.second < b.second;
}

// Function that finds the N approximate nearest neighbors
vector<pair<string, double>> HashTable::findNN(vector<unsigned long> &q, int N)
{
    vector<pair<string, double>> b;
    
    // For each hash table
    for (int i = 0; i < L; i++) {
        
		// Get the bucket that query 'q' belongs in
        unsigned int hashValue = g_func(q, this->TableSize, i);
        
        // For each item in the bucket
        for(auto candidate : hashTables[i][hashValue % TableSize])
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

// Function that finds all the points within a certain radius 'R' of query 'q'
vector<string> HashTable::rangeSearch(vector<unsigned long> &q, double R)
{
    vector<string> b;
    
    // For each hash table
    for (int i = 0; i < L; i++) {
        
		// Get the bucket that query 'q' belongs in
        unsigned int hashValue = g_func(q, this->TableSize, i);
        
        // For each item in the bucket
        for(auto candidate : hashTables[i][hashValue % TableSize])
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

void HashTable::deleteHash()
{
    
}