#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std; 


int main(){
  double a, sum, variance, mean;
  ifstream data("datensumme.txt");
  // while(! data.eof()){
  for(int i = 0; i < 234; i++)
  {
    data >> a;
    sum += a;
  }
  mean = sum/234; 

  cout <<  "Mean: " << mean << endl;
  // data.seekg(0, data.beg);
  data.seekg(0);

  // Calculate variance: 
  for(int i = 0; i < 234; i++)
  {
    data >> a;
    variance += pow(a-mean, 2) / 234;
  }

  cout << "Variance: " << variance << endl;
  
  // Calculate stdev: 
  cout << "Stdev: " << sqrt(variance) << endl;
}