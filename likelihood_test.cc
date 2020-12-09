#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>

using namespace std;

// Calculating poisson function: 
double poisson(double mu, int k)
{
    return pow(mu, k) * exp(-mu) / tgamma(k + 1); 
}

// Calculating likelihood function: 
double prob(vector<int> daten, double mu)
{
    double likelihood = 1; 

    for(int i = 0; i < 234; i++)
    {
        likelihood *= poisson(mu, daten[i] ) ; 
    }

    return likelihood; 
}

int main()
{
    int N = 234;
    double number; 
    double mu = 3.11538; 

    // Creating vector object with 234 entries: 
    vector<int> daten(234);

    /* Read in all N = 234 values from "datensumme.txt" and store them in the 
    vector daten. */
    ifstream fin("datensumme.txt"); 
    for(int i = 0; i < N; i++)
    {
        fin >> number;
        // increment corresponding entry in vector:
        daten[i] = number; 
    }
    fin.close(); 

    cout << prob(daten, mu) << endl; 
    
    return 0; 
}