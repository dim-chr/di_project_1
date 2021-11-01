
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

void init_hashing(int k, int L, int d, unsigned int TableSize)
{
    // Init
    srand( time(0) );
    
    window = rand() % 5 + 2;
    
    hashTables = new HashTable(L, TableSize);
    
    
    //For each h(p) function creat k static r. 
    {
        default_random_engine generator;
        uniform_int_distribution<int> distribution( 1, 10 );

        for (int i = 0; i < k; i++) {

            r.push_back( distribution(generator) );
        }
    }

    // Ftiaxnoume ta t
    {
        default_random_engine generator;
        uniform_real_distribution<double> distribution( 0, window );

        for (int i = 0; i < k; i++) {

            t.push_back( distribution(generator) );
        }
    }
    
    // Ftiaxnoume ta v
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
    
    // Ftiaxnoume ta g
    g.resize(L);
    for (int i = 0; i < L; i++) {
        
        for (int j = 0; j < k; j++) {
            
            int h = rand() % k;

            while( find( g[i].begin(), g[i].end(), h ) != g[i].end() ) //if already exist...
            {
                h = rand() % k;
            }

            g[i].push_back(h);
        }
    }

}

unsigned int h_func( const vector<unsigned long> &p, int i)
{
    
    double dot_product=0.0;
    
    // Diasxizoume to dianisma p gia na ypologisoume to ginomeno p*v
    // d einai kathe oros
    for( int j=0; j<p.size(); j++ )
    {
        dot_product += p[j] * v[i][j];
    }
    
    return (unsigned int) floor( (dot_product + t[i]) / window );
}

unsigned int g_func( const vector<unsigned long> &p, unsigned int TableSize, int i)
{
    unsigned long sum=0;
    
    for( int j=0; j<g[0].size(); j++ )
    {
        sum += r[j] * h_func(p, g[i][j]);
    }
    
    return (unsigned int) ((sum % M) % TableSize);
}


/*======================================================*/


pair<string, vector<unsigned long>> * VectorData::insert(string id, const vector<unsigned long> &v )
{
    vectors.push_back(make_pair( id, v));
    
    // Pairnoume to teleutaio stoixeio (diladi auto pou molis mmpike)
    // gia na mathoume tin dieuthinsi mnimis tou
    pair<string, vector<unsigned long>> &p = vectors.back();
    
    // epistrefoume tin DM tou
    return &p;
}

unsigned int VectorData::size()
{
    return vectors.size();
}


/*=======================================================*/

HashTable::HashTable(int L, unsigned int TableSize)
{
    this->L = L;
    this->TableSize = TableSize;

    // Ftiaxnw posous pinakes thwloume
    hashTables.resize( L );

    // Gia kathe pinaka katakermatismou ftiaxnw tous koubades tou
    for (int i = 0; i < L; i++) {
        hashTables[i].resize( TableSize);
    }
}

void HashTable::insert( int l, string id, vector<unsigned long> &p )
{
    // An to l einai stous pinakes katakermatismou
    if( l < this->L )
    {
        
    }
}