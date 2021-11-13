
#ifndef CLUSTER_H
#define CLUSTER_H

#include <vector>
#include <utility>
#include <string>
#include <cmath>
#include <algorithm>
#include <random>

using namespace std;

class Clusters
{
    private:
        int k;
        vector<vector<double>> centroids;        // Syntetagmenees kentrwn
        vector<vector<pair<string, vector<double>> *>> clusters;
    
    public:
        
        Clusters(int k);
        void kmeans();
        void updateClusters();
        void chooseNewCentroid();
        void Lloyd();
        vector<double> mean(int c);
        bool updateCentroids();
};

extern Clusters *clusters;


void init_clusters(int k);
void Cluster_pre_process(string filename);
void DeallocateMemoryClusters();

#endif /* CLUSTER_H */

