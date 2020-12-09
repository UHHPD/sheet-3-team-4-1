#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <list>

/*Calculate poisson pdf for input mean and observations*/
std::vector<int> daten(std::string filename, int length);

/*Calculate poisson pdf for input mean and observations*/
double poisson(double mu, int k);

/*Calculate the likelihood to observe input sample given input mean of poisson distribution*/
double prob(std::vector<int> input, double mu);

/*Write a textfile containing the likelihoods of the input sample for a range of mean values of the poisson distribution*/
void writeLikelihoods(std::vector<int> Input);



int main(){
  std::vector<int> vec = daten("datensumme.txt", 234);
  writeLikelihoods(vec);

}



/*Function definitions*/
std::vector<int> daten(std::string filename, int length){
  std::ifstream file(filename);
  std::vector<int> daten(length);

  for(int i = 0; i<length; i++){
    file >> daten[i];
  }
  file.close();
  return daten;
}

double poisson(double mu, int k){
  double p = pow(mu, k)*exp(-mu)/tgamma(k+1);
  return p;
}

double prob(std::vector<int> input, double mu){
  double LH = 1;
  for(int k = 0; k< input.size(); k++){
    LH *= poisson(mu, input[k]);
  }
  return LH;
}

void writeLikelihoods(std::vector<int> Input){
  std::ofstream Likelihoods("Likelihood.txt");
  for(double i = 0; i <= 6; i+= 0.1){
    Likelihoods << i << ' ' << prob(Input, i) << std::endl;
  }
  Likelihoods.close();
}

void substract()
