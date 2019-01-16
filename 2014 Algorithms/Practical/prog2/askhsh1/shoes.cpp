#include<iostream>

using namespace std;
typedef long long int ulong;

int L,R;
int lefttype[102];
int righttype[102];
ulong leftamount[102];
ulong rightamount[102];

struct amountpair {
  amountpair* prev;
  amountpair* next;
  ulong x;
  ulong y;
  ulong solution;
};

amountpair* Shoes[102][102];

ulong max(ulong x,ulong y) {
  if(x>y) return x;
  else return y;
}

ulong shoes(int i,ulong ai, int j, ulong bj) {
  if(i>L||j>R) return 0;
  else {
    amountpair* var=new amountpair;
    if(Shoes[i][j]==NULL) {
      var->prev=NULL;
      var->next=NULL;
      var->x=ai;
      var->y=bj;
      var->solution=0;
      Shoes[i][j]=var;
    }
    else {
      var=Shoes[i][j];
      bool found=false;
      while(var->next!=NULL&&!found) {
        if(var->x==ai&&var->y==bj) found=true;
        else var=var->next;
      }
      if(found==false) {
        amountpair* varnew=new amountpair;
        varnew->prev=var;
        varnew->next=NULL;
        var->next=varnew;
        varnew->x=ai;
        varnew->y=bj;
        varnew->solution=0;
        var=varnew;
      }
    }
    ulong finsol=var->solution;
    if(finsol==0) {
      if(lefttype[i]!=righttype[j]) finsol=max(shoes(i,ai,j+1,rightamount[j+1]),shoes(i+1,leftamount[i+1],j,bj));
      else {
        if(ai==bj) finsol=ai+shoes(i+1,leftamount[i+1],j+1,rightamount[j+1]);
        else if(ai>bj) finsol=bj+shoes(i,ai-bj,j+1,rightamount[j+1]);
        else finsol=ai+shoes(i+1,leftamount[i+1],j,bj-ai);
      }
      var->solution=finsol;
    }
    return finsol;
  }
}


int main() {
  cin>>L;
  cin>>R;
  for(int i=1;i<=L;i++) {
    cin>>leftamount[i];
    cin>>lefttype[i];
  }
  for(int i=1;i<=R;i++) {
    cin>>rightamount[i];
    cin>>righttype[i];
  }
  cout<<shoes(1,leftamount[1],1,rightamount[1])<<endl;
  return 0;
}

