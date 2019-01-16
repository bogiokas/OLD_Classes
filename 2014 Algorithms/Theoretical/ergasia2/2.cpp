#include<iostream>

using namespace std;

int n=5;
int A[6][2]; //A[i][0]=a_i, A[i][1]=v_i
int B[6][2]; //B[i][0]=b_i, B[i][1]=j (the A card matched)
int score=0; //solution

int quickselectB(int x, int start, int end) {
  int med=(start+end)/2;
  if(start==end) return start;
  if(x<=B[med][0]) return quickselectB(x,start,med);
  else return quickselectB(x,med+1,end);
}

void greedy(int i) {
  int l=quickselectB(A[i][0], 1, n);
  if(l>0) {
    while(B[l][1]>0&&l>0) l--;
    if(l>0) {
      B[l][1]=i;
      score+=A[i][1];
    }
  }
  if(l==0) {
    int p=n;
    while(B[p][1]>0) p--;
    B[p][1]=i;
  }
  if(i<n) greedy(i+1);
}

int main() {
//input, sorting
  greedy(1);
//output
  return 0;
}