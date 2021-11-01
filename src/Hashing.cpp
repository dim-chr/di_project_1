
#include "Hashing.h"

#include <cstdlib>
#include <ctime>
#include <random>
#include <algorithm>
#include <cmath>

/*
 * 
 * 
 * 
 * 
 * TODO: Svinoume to hashTbales pou egine me new
 * */

#define M 4294967291        // 2^32 - 5

int window;     // w
vector<int> r;
vector<vector<int>> g; // {[1,2,3][3,5,3][5,6,3][9,4,5]} = {[r1*h1+r2*h2 etc][r1*h3+r2*h5 etc], etc.. }
vector<double> t;
vector<vector<double>> v;

HashTable *hashTables;

using namespace std;

// Function that is used to initialize all the necessary variables and data structures in order to use the hash functions and the hash tables
void init_hashing(int k, int L, int d, unsigned int TableSize)
{
    // Init
    srand(time(0));
    
    window = rand() % 5 + 2;
    
    hashTables = new HashTable(L, TableSize);
    
    

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
        normal_distribution<double> distribution( 0.0, 1.0 );

        v.resize(k);

        /*
        [[4,5,6][2,4,5][][]]
        ****k*****
        */
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
    
    return (unsigned int) ((sum % M) % TableSize);
}


/*======================================================*/


// Function that is used to insert each vector in the list
pair<string, vector<unsigned long>> * VectorData::insert(string id, const vector<unsigned long> &v)
{
    vectors.push_back(make_pair(id, v));  // Insert the 'item_id' of vector 'p' and its coordinates
    
    // Get the item that was just inserted in the list
    pair< string, vector<unsigned long>> &p = vectors.back();

    
    // Return the item's address
    return &p;
}

// Function that returns the size of the list
unsigned int VectorData::size()
{
    return vectors.size();
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

void HashTable::insert(int l, string id, vector<unsigned long> &p)
{
    // An to l einai stous pinakes katakermatismou
    if(l < this->L)
    {
        hashValue = g_func(p, this->TableSize, l);
		
		hashTables[l][hashValue].push_back();
    }
}