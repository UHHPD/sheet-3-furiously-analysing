#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>


double poisson(double mu, int k) {
    using namespace std;
    double P= pow(mu, k) * exp(- mu) / tgamma(k + 1);
    return P;
}

int main() {
    using namespace std;
    vector<int> zaehler(11);
    int N = 234;

    ifstream fin("datensumme.txt");
    int n_i;
    for(int i = 0 ; i < N ; ++i) {
        fin >> n_i;
        zaehler[n_i] +=1;
    }
    fin.close();
    
    ofstream hist("hist.txt");
    for(unsigned int k = 0 ; k < zaehler.size() ; ++k){
      hist << k << " " << zaehler[k] << endl;
    }
    hist.close();

    ofstream histpoi("histpoi.txt");
    for(unsigned int k = 0 ; k < zaehler.size() ; ++k){
      histpoi << k << " ";
      histpoi << zaehler[k] << " ";
      histpoi << N * poisson(3.11538, k) << endl;
    }
    histpoi.close();
}