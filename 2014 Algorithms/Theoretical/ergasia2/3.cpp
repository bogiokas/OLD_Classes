#include<iostream>

using namespace std;

struct node {
  node* prev;
  node* next;
  int name;
};
int n=5;
node N[6];
int w[6];
int dynweight[6][2];

int max(int x,int y) {
  if(x>y) return x;
  else return y;
}

int weight(node u,node v, bool sign) {
  int solution=0;
  node p=N[u.name];
  while(p.next!=NULL) {
    if(p.name!=v.name) {
      if(sign) {
        if(dynweight[p.next->name][0]==0) dynweight[p.next->name][0]=weight(*(p.next),u,!sign);
        solution+=dynweight[p.next->name][0];
      }
      else {
        if(dynweight[p.next->name][0]==0) dynweight[p.next->name][0]=weight(*(p.next),u,sign);
        if(dynweight[p.next->name][1]==0) dynweight[p.next->name][1]=weight(*(p.next),u,!sign);
        solution+=max(dynweight[p.next->name][0],dynweight[p.next->name][1]);
      }
    }
    p=*(p.next);
  }
  if(sign) solution+=w[u.name];
  return solution;
}

int main() {
//input
node foo={NULL,NULL,0};
int final=max(weight(N[1],foo,true),weight(N[1],foo,false));
//output
return 0;
}
