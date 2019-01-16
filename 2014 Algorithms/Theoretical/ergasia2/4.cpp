#include<iostream>

using namespace std;

int N=4;
int Q=8;
int w[5];
int A[8];
int b[5];
int barb;
double B[5];

void makeA() {
  A[0]=1;
  int B[Q];
  for(int i=1;i<=N;i++) {
    for(int j=0;j<Q;j++) B[j]=0;
    int k=0;
    while(k+w[i]<Q) {
      B[k+w[i]]=A[k];
      k++;
    }
    for(int j=0;j<Q;j++) A[j]+=B[j];
  }
}

void makeb() {
  for(int i=1;i<=N;i++) {
    for(int k=Q-w[i];k<Q;k++) {
      for(int s=0;s<=k/w[i];s++) {
        if(s%2==0) b[i]+=A[k-w[i]*s];
        else b[i]-=A[k-w[i]*s];
      }
    }
  }
}

void makebarb() {
  for(int i=1;i<=N;i++) barb+=b[i];
}

void makeB() {
  for(int i=1;i<=N;i++) B[i]=(double)b[i]/barb;
}

int main() {
  w[1]=5;
  w[2]=3;
  w[3]=2;
  w[4]=2;

  makeA();
  makeb();
  makebarb();
  makeB();

  for(int k=0;k<Q;k++) {
    cout<<A[k]<<" ";
  }
  cout<<endl;
  for(int i=1;i<=N;i++) {
    cout<<b[i]<<" ";
  }
  cout<<endl;
  cout<<barb<<endl;
  for(int i=1;i<=N;i++) {
    cout<<B[i]<<" ";
  }
  cout<<endl;


  return 0;
}
