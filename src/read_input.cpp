#include "read_input.h"
#include <math.h>
#include <sstream>
#include "Configuration.h"
#include "Hashing.h"


void preprocessing(string filename, int L)
{
    vector<unsigned long> p;
    
    // anoigw to arxceio
    ifstream inputFile(filename);

    if (inputFile)
    {
        string line;

        // GIa kathe grammi
        while (getline(inputFile, line))
        {
            char* buff = new char[line.length()+1];
            strcpy(buff, line.c_str());
            char* token = strtok(buff," \t");

            char *id = token;

            token = strtok(buff," \t");
            // gia kathe diastasi - syntetagmeni
            while (token != NULL)
            {
                p.push_back(atoi(token));
                token = strtok (NULL, " \t");
            }

            // Gia kathe pinaka katakermatismou
            for (int i = 0; i < L; i++) {

                //hashTables->insert( id, p );
            }

                        // paei ston pinaka
                        // ....

                        // adeiazw to p
            delete[] buff;
            p.clear();
        }

        inputFile.close();
    }
}

void read_configuration(string filename)
{
    Configuration *c = c->getInstace();

    ifstream infile(filename);
    string  attr; 
    int val = 0;

    while (getline(infile, attr))
    {   
        /*
        Getting the integer value from each file line. 
        If not exist, it returns 0.
        Then setting the data to the object.
        */
        val = extractIntegerFromString(attr); 
        c->setData(val); 
    }
    
    c->globalDataInit();
    //c->printData();
    
    infile.close();
}


int extractIntegerFromString(string str)
{
    stringstream ss;    
  
    /* Storing the whole string into string stream */
    ss << str;
  
    /* Running loop till the end of the stream */
    string temp;
    int found = 0;
    while (!ss.eof()) {
  
        /* extracting word by word from stream */
        ss >> temp;
  
        /* Checking the given word is integer or not */
        if (stringstream(temp) >> found)
            return found;
        /* To save from space at the end of string */
        temp = "";        
    }
    return 0;
}