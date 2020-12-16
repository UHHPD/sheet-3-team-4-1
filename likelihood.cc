#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <list>

using namespace std;

double poisson(double mu, int k) {
    double p = pow(mu, k) * exp(-mu)/ tgamma(k+1);
    return p;
}

vector<int> daten(234);

// This function computes the likelihood: 
double likelihood(vector<int> daten, double mu)
{
  double l=1;
  for(int i = 0 ; i < 234 ; ++i) 
  {
    l *= poisson(mu, daten[i]);
  }
  return l;
} 

int main() { 

    ifstream fin("datensumme.txt");
    ofstream f_likelihood("likelihood.txt"); 
    ofstream f_loglikeli("nll.txt");
    ofstream f_subtraction("deltanll.txt");

    int n;
    
    for(int i = 0 ; i < 234 ; ++i) {
        fin >> n;
        daten[i] = n;
    }
   fin.close();
  
  double delta [601]; 
  

  // Task 2a: 
  cout << "Likelihood: " << likelihood(daten, 3.11538) << endl; 

  
  for(double mu = 0.0 ; mu <= 6; mu= mu+0.01)
  {
    f_likelihood <<mu << " " << likelihood(daten, mu) << endl;
    f_loglikeli << mu << " " << -2*log(likelihood(daten, mu))<< endl;
    f_subtraction << mu << " " << -2*log(likelihood(daten, mu)) +2*log(likelihood(daten, 3.11358)) << endl;
    //cout << mu << endl;
  }

  double mu = 0; 
  double estimator[601];
  
  for(int i = 0; i < 601; i++)
  {
    estimator[i] = mu;
    delta[i] = -2*log(likelihood(daten, mu)) + 2*log(likelihood(daten, 3.11358));
    mu += 0.01;
    // cout << delta [i] << endl;
  }
  

  cout << delta [0] << endl;
   // Find the position in the vector where the minimum is stored. 
  int arg_min = 0; 
  // Find minimum: 
  double min = 10; 
  
  for(int i = 0; i < 601; i++)
  {


    if(delta[i] < min)
    {
      min = delta[i];
      arg_min = i; 

    }
  }
  // cout << "argmin: " << arg_min << endl; 
  cout << "calculated min: " << estimator[arg_min] << endl; 
  
  // Determine uncertainty on estimated \hat{mu}. 
  list <double> interval;
  double uncertainty[601];

  for(int i = 0; i < 601; i++)
  {
    uncertainty[i] = -2*log(likelihood(daten, estimator[i])) +2*log(likelihood(daten, estimator[arg_min]));
    
    if(uncertainty[i] < 1.0)
    {
      // cout << estimator[i] << endl;
     interval.push_back(estimator[i]); 
    }
  }

  // l.back(): Get last item of list. 
  cout << "Uncertainty on estimator: " << interval.back() - estimator[arg_min] << endl;
  
   // From a previous exercise: 
  double standard_dev_datensumme = 1.65365; 
  // Comparison with sample mean: 
  cout << "Uncertainty on the sample mean: " << standard_dev_datensumme/sqrt(234) << endl;

  // "reset" mu: 
  mu = 3.11538; 
  // Compute likelihood ratio and relative deviation of likelihood ratio from the mean//
  double ratio = likelihood(daten, mu); 
  double denominator = 1;

  cout << "mu: " << mu << endl; 
  
  for(int i = 0; i < 234; i++)
  {
    denominator *=  poisson(daten[i], daten[i]);
  }  

  ratio = ratio/denominator; 

  // Print out ratio: 
  cout << "ratio: " << ratio << endl; 
  

  // relative deviation, ndof: number of degress of freedom, parameter of \chi^2 distribution
  static int ndof = 233; 

  cout << "-2*ln(lambda): " << -2*log(ratio) << endl; 

  double deviation =  (-2*log(ratio) - ndof )/( sqrt(2*ndof) );

  cout << "Relative deviation: " << deviation << endl; 

  return 0; 
}