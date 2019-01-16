#include<iostream>
#include <algorithm>

using namespace std;
typedef unsigned long int ulong;
ulong dist(ulong a,ulong b) {
  if(a>b) return a-b;
  else return b-a;
}

int main() {
  ulong N;
  cin>>N;
  ulong A[N][2],X[N],Y[N];
  for(ulong i=0;i<N;i++) {
    cin>>A[i][0];
    X[i]=A[i][0];
    cin>>A[i][1];
    Y[i]=A[i][1];
  }
  sort(X,X+N);
  sort(Y,Y+N);
  ulong distance=0;
  for(ulong i=0;i<N;i++) distance+=dist(X[N/2-1],A[i][0])+dist(Y[N/2-1],A[i][1]);
  cout<<endl<<X[N/2-1]<<" "<<Y[N/2-1]<<" :"<<distance<<endl<<endl;
  ulong B[N];
  for(ulong i=0;i<N;i++) {
    B[i]=0;
    for(ulong j=0;j<N;j++) {
      B[i]+=dist(A[i][0],A[j][0])+dist(A[i][1],A[j][1]);
    }
  }
  for(ulong i=0;i<N;i++) cout<<A[i][0]<<" "<<A[i][1]<<": "<<B[i]<<endl;
  return 0;
}
