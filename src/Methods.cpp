#include "Methods.h"
#include "LshHashing.h"
#include "CubeHashing.h"

#include "VectorData.h"

// Function that reads all the points from the input file and saves them in the appropriate data structures
void LSH_pre_process(string filename, int L)
{
    vector<unsigned long> p;
    
    // Open the input file
    ifstream inputFile(filename);

    if (inputFile)
    {
        string line;

        // Read every line of the file
        while (getline(inputFile, line))
        {
            char* buff = new char[line.length()+1];
            strcpy(buff, line.c_str());
            char* token = strtok(buff," \t");

            char *id = token;  // This is the 'item_id' of the point

            token = strtok(NULL," \t");

            // Read all the coordinates of the point and store them in vector 'p'
            while (token != NULL)
            {
                p.push_back(atoi(token));
                token = strtok (NULL, " \t");
            }

            // Insert the 'item_id' of the point and its coordinates in the 'vectorData' list
            // The 'VectorData::insert' function returns the address of the pair (id, p) that was just inserted in the list
            pair<string, vector<unsigned long>> * vectorDataPointer =  vectorData->insert(id, p);
            
            // Insert the point in every hash table
            for (int i = 0; i < L; i++) {

                LSH_hashTables->LSH_insert(i, p, vectorDataPointer);
            }
            
            delete[] buff;
            p.clear();
        }

        inputFile.close();
    }

    LSH_hashTables->printHash();
}
// Function that reads all the points from the input file and saves them in the appropriate data structures
void Cube_pre_process(string filename, int d)
{    
    vector<unsigned long> p;
    
    // Open the input file
    ifstream inputFile(filename);

    if (inputFile)
    {
        string line;

        // Read every line of the file
        while (getline(inputFile, line))
        {
            char* buff = new char[line.length()+1];
            strcpy(buff, line.c_str());
            char* token = strtok(buff," \t");

            char *id = token;  // This is the 'item_id' of the point

            token = strtok(NULL," \t");

            // Read all the coordinates of the point and store them in vector 'p'
            while (token != NULL)
            {
                p.push_back(atoi(token));
                token = strtok (NULL, " \t");
            }

            // Insert the 'item_id' of the point and its coordinates in the 'vectorData' list
            // The 'VectorData::insert' function returns the address of the pair (id, p) that was just inserted in the list
            pair<string, vector<unsigned long>> * vectorDataPointer =  vectorData->insert(id, p);
            
            // Insert the point in every hash table
        
            C_hashTables->Cube_insert(d, p, vectorDataPointer);


            delete[] buff;
            p.clear();
        }

        inputFile.close();
    }
}


// Function that reads all the query points from the query file and executes the LSH and Range Search algorithms
// It also generates the output file with the results
void lsh(string input, string output, int N, double R)
{
    vector<unsigned long> q;
    
    // Open the input and output files
    ifstream inputFile(input);
    
    ofstream outputFile(output);

    if (inputFile)
    {
        string line;
unsigned long correct=0;
unsigned long quer=0;
        // Read every line of the file
        while (getline(inputFile, line))
        {quer++;
            char* buff = new char[line.length()+1];
            strcpy(buff, line.c_str());
            char* token = strtok(buff," \t");

            char *id = token;

            token = strtok(NULL," \t");

            // Read all the coordinates of the query and store them in vector 'q'
            while (token != NULL)
            {
                q.push_back(atoi(token));
                token = strtok (NULL, " \t");
            }

            // Find the N nearest neighbors using the LSH algorithm, their distance from 'q' and the time it takes to find them
            auto startLSH = chrono::steady_clock::now();
            vector<pair<string, double>> nn = LSH_hashTables->LSH_findNN(q, N);
            auto endLSH = chrono::steady_clock::now();

            // Find the real distances of the N nearest neighbors from 'q' and the time it takes to find them
            auto startRealDist = chrono::steady_clock::now();
            vector<pair<string, double>> bf =  vectorData->findRealDistBruteForce(q, N);
            auto endRealDist = chrono::steady_clock::now();
            
            // Find all the points within radius 'R' of 'q'
            set<string> rs = LSH_hashTables->LSH_rangeSearch(q, R);
            
            outputFile << "Query: " << id << endl;
            
            // Write all the results in the output file
            unsigned int j = 1;
            for(unsigned int i = 0; i < nn.size(); i++)
            {
                outputFile << "Nearest neighbor-"<< j << ": " << nn[i].first << endl;
                outputFile << "distanceLSH: "<< nn[i].second << endl;
                outputFile << "distanceTrue: "<< bf[i].second << " | " << bf[i].first << endl;
                correct = correct + (nn[i].first==bf[i].first ? 1 : 0);
                j++;
            }
            
            outputFile << "tLSH: " << chrono::duration_cast<chrono::microseconds>(endLSH - startLSH).count() << " μs" << endl;
            outputFile << "tTrue: " << chrono::duration_cast<chrono::microseconds>(endRealDist - startRealDist).count() << " μs" << endl;
            
            outputFile << "R-near neighbors:" << endl;
            for(auto s : rs)
            {
                outputFile << s << endl;
            }
            outputFile << endl;

            delete[] buff;
            q.clear();
        }
cout << 100*((double)correct / (quer*N)) << "%%" <<endl;
        inputFile.close();
        outputFile.close();
    }
}