#include<iostream>

using namespace std;

int N;
int p[2501];

int w[2501][2501];
int best[2501][2501];

int min(int x,int y) {
  if(x<y) return x;
  else return y;
}

int computew(int i, int j) {
  if(i>j) return 0;
  else {
    if(w[i][j]==0) {
      if(i==j) w[i][j]=p[i];
      else w[i][j]=p[j]+computew(i,j-1);
    }
    return w[i][j];
  }
}

int computebest(int i, int j) {
  if(i>=j) return 0;
  else {
    if(best[i][j]==0) {
      int sol=0;
      int bestk;
      int leftinv;
      for(int k=i;k<j;k++) {
        int foo=min(computebest(i,k)+computew(i,k),computebest(k+1,j)+computew(k+1,j));
        if(foo>sol) {
          sol=foo;
          bestk=k;
          if(foo==computebest(i,k)+computew(i,k)) leftinv=false;
          else leftinv=true;
        }
      }
      cout<<i<<" "<<bestk<<" "<<j;
      if(leftinv) cout<<" left"<<endl;
      else cout<<" right"<<endl;
      best[i][j]=sol;
    }
  }
  return best[i][j];
}

int main() {
  cin>>N;
  for(int i=1;i<=N;i++) cin>>p[i];
  cout<<computebest(1,N)<<endl;
/*  for(int i=1;i<=N;i++) {
    for(int j=1;j<=N;j++) {
      cout<<best[i][j]<<" ";
    }
    cout<<endl;
  }
*/  return 0;
}
