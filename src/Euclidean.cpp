#include <cmath>
#include "Euclidean.h"

using namespace std;

// Function that calculates the euclidean distance between two points
double euclidean_distance(const vector<unsigned long> &p, const vector<unsigned long> &q)
{
    double sum = 0.0;
    
    for(int i=0; i<p.size(); i++)
    {
        sum = sum + pow(abs((long) p[i] - (long)q[i]), 2.0);
    }
    
    return sqrt(sum);
}

// Function that performs the euclidean modulo operation
unsigned long euclidean_mod(long x, long y)
{
    if(y != 0)
    {
        int r = x % y;

        return r >= 0 ? r : r + abs(y);
    }
    
    return 0;
}