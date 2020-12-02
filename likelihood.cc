#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>


double poisson(double mu, int k) {
  using namespace std;
  double P= pow(mu, k) * exp(- mu) / tgamma(k + 1);
  return P;
}

double prob(std::vector<int> daten, double mu){
  double L = 1;
  for(unsigned int k = 0 ; k < daten.size() ; ++k){
  L *= poisson(mu, daten[k]);
  }
  return L;
}

int main() {
    using namespace std;
    double mu_true = 3.11538;

    vector<int> daten;
    ifstream fin("datensumme.txt");
    int n_i;
    for(int i = 0 ; i < 234 ; ++i) {
        fin >> n_i;
        daten.push_back(n_i);
    }
   fin.close();

  cout << prob(daten, mu_true) << endl;

  ofstream llhfile("likelihood.txt");
  for(double mu = 0 ; mu <= 6 ; mu += 0.01){
    llhfile << mu << " " << prob(daten, mu) << endl;
  }
  llhfile.close();

  ofstream lllhfile("nll.txt");
  for(double mu = 0 ; mu <= 6 ; mu += 0.01){
    lllhfile << mu << " " << -2*log(prob(daten, mu)) << endl;
  }
  lllhfile.close();


  ofstream nllfile("deltanll.txt");
  for(double mu = 0 ; mu <= 6 ; mu += 0.01){
    nllfile << mu << " " << -2*log(prob(daten, mu)) + 2* log(prob(daten, mu_true))<< endl;
  }
  nllfile.close();

double mu_est, mu_maxstd, mu_minstd, mu_std, std_sample, denominator, lambda;
// estimate for mu_true from plot : 3.12
  mu_est = 3.12;
// estimate function ==1 in plot
  mu_minstd = 3.0;
  mu_maxstd = 3.23;
  mu_std = (mu_maxstd - mu_minstd)/2;

//compare to uncertainty in sample mean
std_sample = 1.65365 / sqrt(234);
cout << "Std from Llh: " << mu_std << endl;
cout << "Std of sample mean: " << std_sample <<endl;
// are the same wit h respect to our accuracy of 0.01

denominator = 1;
for(unsigned int k = 0 ; k < daten.size() ; ++k){
  denominator *= poisson(daten[k], daten[k]);
}

lambda = prob(daten,mu_true) / denominator;
cout << "likelihood ratio: \n";
cout << lambda << endl;

double z;
z = (-2* log(lambda) - 233) / (sqrt(466));
cout << z << endl;
}    