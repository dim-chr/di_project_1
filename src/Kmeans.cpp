

#include "Kmeans.h"
#include "VectorData.h"
#include "Euclidean.h"

using namespace std;

#define STOP 20

Clusters *clusters;

void init_clusters(int k)
{
    srand(time(NULL));
    
    vectorData = new VectorData();
}

Clusters::Clusters(int k)
{
    this->k = k;
    clusters.resize(k);
    
    unsigned int random_point = rand() % vectorData->size();
    
    vector<double> c = vectorData->get(random_point ).second;
    
    centroids.push_back( c );
}

void Clusters::kmeans()
{
    for (int i = 0; i < k-1; i++) {
        
        updateClusters();
        chooseNewCentroid();
    }
}

void Clusters::updateClusters()
{
    clusters.clear();
    clusters.resize(k);
    
    for(auto v : vectorData->getBegin())
    {
        int newC=-1;;
        double min = INT32_MAX;
        
        for (int c=0; c<centroids.size() ; c++) {

            double dist = euclidean_distance( v.second, centroids[c] );
            
            if(  dist < min ){
                min =dist;
                newC = c;
            }
        }
        
        // Paei sto kainourgio cluster
        clusters[newC].push_back( &(v) );
    }
}

void Clusters::chooseNewCentroid()
{
    vector<double> sums;
    sums.push_back(0);
    
    for(auto v : vectorData->getBegin())
    {
        double max = 0;
        double min = INT32_MAX;
        
        for (int c=0; c<centroids.size() ; c++) {

            double dist = euclidean_distance( v.second, centroids[c] );
            if( dist == 0.0 )
                continue;
                    
            if(  dist < min ){
                min =dist;
            }
            
            if(  dist > max ){
                max =dist;
            }
        }
        
        if( min == INT32_MAX ){
            continue;
        }
        
        double di = pow(min / max, 2.0);
        sums.push_back( sums.back() + di );
    }
    
    default_random_engine generator(time(NULL));
    uniform_real_distribution<double> distribution(0, sums.back());
    double x = distribution(generator);
    
    unsigned int r=0;
    while(r < sums.size()){
        
        if( sums[r] < x && x <= sums[r+1] ){
            r++;
            break;
        }
        
        r++;
    }
    
    vector<double> c = vectorData->get( r ).second;
    centroids.push_back(c);
}

void Clusters::Lloyd()
{
    bool b;
    
    do{
        
        updateClusters();
        b = updateCentroids();
        
        
    }while(!b);
}

bool Clusters::updateCentroids()
{
    vector<double> newDist;
    
    for (int i=0; i<centroids.size(); i++) {

        vector<double> m = mean( i );
        double dist = euclidean_distance( centroids[i], m );
        centroids[i] = m;
        newDist.push_back( dist );
    }
    
    // Check an tha mporousa na stamatisw ta update centroids
    for (auto d : newDist) {

        if( d > STOP )
            return false;
    }

    return true;
}

vector<double> Clusters::mean(int c)
{
    vector<double> m = centroids[c];
    
    for (int i = 0; i < m.size(); i++) {
        
        m[i] = 0.0;
        
        for( auto vec : clusters[c] ) {
            
            m[i] = m[i] + (vec->second)[i];
        }
        
        if(clusters[c].empty())
            m[i] = 0.0;
        else
            m[i] = m[i] / clusters[c].size();
    }

    return m;
}

void DeallocateMemoryClusters()
{
    delete vectorData;
    delete clusters;
}