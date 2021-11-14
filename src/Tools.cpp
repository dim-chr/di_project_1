#define _CRT_SECURE_NO_WARNINGS
#include "Tools.h"
#include "Configuration.h"


// Function that is given as an argument to the 'sort' function in order to sort a vector that contains pairs
bool sortbyDist(const pair<string, double> &a, const pair<string, double> &b)
{
    return a.second < b.second;
}

// Function that calculates the hamming distance between two integers
unsigned int HammingDistance(unsigned int a, unsigned int b)
{
    // Get the XOR of the two numbers
    unsigned int Xor = a ^ b;

    // The bits of the XOR between a and b that are 1
    unsigned int bits = 0;

    // Count the numbers of bits that are 1
    while (Xor > 0)
    {
        // If the rightmost bit of 'Xor' is 1 then Xor & 1 = 1
        bits += Xor & 1;

        // Perform right shift on 'Xor' to get the next bits
        Xor >>= 1;
    }

    return bits;
}

/*
void read_configuration(string filename)
{
    Configuration *c = c->getInstace();

    ifstream infile(filename);
    string  attr; 
    int val = 0;

    while (getline(infile, attr))
    {   
        
        // Getting the integer value from each file line. 
        // If not exist, it returns 0.
        // Then setting the data to the object.
        val = extractIntegerFromString(attr); 
        c->setData(val); 
    }
    
    c->globalDataInit();
    
    infile.close();
}
*/

/*
int extractIntegerFromString(string str)
{
    stringstream ss;    
  
    // Storing the whole string into string stream
    ss << str;
  
    // Running loop till the end of the stream
    string temp;
    int found = 0;
    while (!ss.eof()) {
  
        // extracting word by word from stream
        ss >> temp;
  
        // Checking the given word is integer or not
        if (stringstream(temp) >> found)
            return found;
        // To save from space at the end of string
        temp = "";        
    }
    return 0;
}
*/

// Function that finds the number of coordinates that a point has
int dimension(string filename)
{
    int dim = 0; 

    ifstream infile(filename);
    string  line; 

    getline(infile, line);

    dim = count(line.begin(), line.end(), ' ')-1;

    infile.close();

    return dim;
}

// Function that counts the number of lines in a file
int count_file_lines(string filename)
{
    int count = 0;
    ifstream infile(filename);
    if (infile)
    {
        string line;
        while (getline(infile, line))
        {
            count++;
        }
    }
    infile.close();
    return count;
}