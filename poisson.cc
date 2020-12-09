#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

ifstream fin("datensumme.txt");

double poisson(double mu, int k) {
    double p = pow(mu, k) * exp(-mu)/ tgamma(k+1);
    return p;
}

vector<int> getFreq(ifstream& input){
  vector<int> zaehler(11);
  int n;
  for(int i = 0 ; i < 234 ; ++i) {
    input >> n;
    zaehler[n] += 1; 
    }
  input.close();
  return zaehler;
}

void writeHist(vector<int>& input){
  ofstream fout("hist.txt");
  
  for(int i=0; i< input.size(); i++){
   fout << i << " " << input[i]<< endl ;
  }
fout.close();
}

void writeHistPoi(vector<int>& input, double mu){
  ofstream fout("histpoi.txt");
  
  for(int i=0; i< input.size(); i++){
   fout << i << " " << input[i]<<  " " << 234* poisson(mu, i) << endl ;
  }
fout.close();
}

int main() {
  double mu = 3.11538;
  vector<int> zaehler = getFreq(fin);
  writeHistPoi(zaehler, mu);
}
