#include<iostream>
#include<limits.h>
using namespace std;

int n=3,k=2;
int room[4];
int last[3];
int request[4][2];

void greedy(int i) {
  int mins=0;
  int mind=INT_MAX;
  for(int s=1;s<=k;s++) {
    if(request[i][0]>=last[s]&&mind>request[i][0]-last[s]) {
      mins=s;
      mind=request[i][0]-last[s];
    }
  }
  if(mins>0) {
    last[mins]=request[i][1];
    room[i]=mins;
  }
  if(i<n) greedy(i+1);
}

int main() {
  for(int i=1;i<=n;i++) {
    cin>>request[i][0];
    cin>>request[i][1];
  }
  greedy(1);
  for(int i=1;i<=n;i++) if(room[i]>0) cout<<"request "<<i<<": "<<room[i]<<endl;
  return 0;
}
