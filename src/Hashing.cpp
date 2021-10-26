
#include "Hashing.h"

#include <cstdlib>
#include <ctime>
#include <random>
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

HashTable *hashTables;

using namespace std;

void init_hashing(int k, int L, unsigned int TableSize)
{
    // Init
    srand( time(0) );
    
    window = rand() % 5 + 2;
    
    hashTables = new HashTable( L, TableSize );
    
    
    // Ftiaxnoume ta ri
    default_random_engine generator;
    uniform_int_distribution<int> distribution( 1, 10 );
    
    for (int i = 0; i < k; i++) {
        
        r.push_back( distribution(generator) );
    }

    
}

unsigned int h( const vector<unsigned long> &p )
{
    default_random_engine generator;
    normal_distribution<double> distribution( 0.0, 1.0 );
    
    double t = distribution(generator);
    
    // [0,w)
    while( t < 0.0 || t >= window )
        t = distribution(generator);
    
    double dot_product=0.0;
    double v;
    
    // Diasxizoume to dianisma p gia na ypologisoume to ginomeno p*v
    // d einai kathe oros
    for( auto d : p )
    {
        v = distribution(generator);
        
        // Isws na min thelei thetikous mono
        while( t < 0.0 )
            v = distribution(generator);
        
        dot_product += d * v;
    }
    
    return (unsigned int) floor( (dot_product + t) / window );
}

unsigned int g( const vector<unsigned long> &p, unsigned int TableSize )
{
    unsigned long sum=0;
    
    for( auto ri : r )
    {
        sum += ri * h(p);
    }
    
    return (unsigned int) ((sum % M) % TableSize);
}


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

void HashTable::insert( string id, vector<unsigned long> &p )
{
    
}