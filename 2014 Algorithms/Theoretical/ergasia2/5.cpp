#include<iostream>
#include<math.h>
using namespace std;

int n=4;
double prob[5];
double prod[5][5];
double E[5];

double produkt(int i, int j) {
  if(i>j) return 1;
  if(prod[i][j]==0) {
    prod[i][j]=1;
    for(int l=i;l<=j;l++) prod[i][j]*=prob[l];
  }
  return prod[i][j];
}  

double profit(int k) {
  if(k==0) return 0;
  else if(E[k]==0) {
    E[k]+=produkt(1,k)*pow(k,4);
    for(int s=1;s<=k;s++) {
      E[k]+=(1-prob[s])*produkt(s+1,k)*(profit(s-1)+pow(k-s,4));
    }
  }
  return E[k];
}

int main() {
  prob[1]=0.8;
  prob[2]=0.6;
  prob[3]=0.5;
  prob[4]=0.5;
  cout<<profit(n)<<endl;
  return 0;
}
