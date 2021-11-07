#include "VectorData.h"
#include "Euclidean.h"

#include <string>
#include <algorithm>


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