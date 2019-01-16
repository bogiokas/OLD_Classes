#include<iostream>

using namespace std;
typedef long long int ulong;
ulong A[100000][2];
ulong N,K;

ulong dist(ulong x,ulong y) {
  if(x>y) return x-y;
  else return y-x;
}

ulong maximum(ulong x,ulong y) {
  if(x>y) return x;
  else return y;
}

bool existssol(ulong m) {
  ulong pointer=A[0][0]-m;
  for(ulong i=0;i<N;i++) {
    pointer+=(A[i][1]-1)*K;
    if(dist(pointer,A[i][0])>m) return false;
    if(i<N-1) pointer=maximum(pointer+K,A[i+1][0]-m);//epilegw an tha synexisw apo to +K h apo m prin thn epoenh thesh
  }
  return true;
}

ulong quickselect(ulong min,ulong max) {
  if(min==max) return min;
  else if(existssol((max+min)/2)) return quickselect(min,(max+min)/2);
  else return quickselect((max+min)/2+1,max);
}

int main() {
  cin>>N;
  cin>>K;
  K*=2; //ta diplasiazw gia na mhn asxoloumai me 0.5
  ulong minsol,maxsol,maxspot;
  maxsol=0;
  cin>>A[0][0];
  cin>>A[0][1];
  A[0][0]*=2;
  maxspot=A[0][0]+K*(A[0][1]-1);
  minsol=(A[0][1]-1)/2*K;
  maxsol=A[0][1]*K;
  for(ulong i=1;i<N;i++) {
    cin>>A[i][0];
    cin>>A[i][1];
    A[i][0]*=2;//omoiws
    maxspot+=K*A[i][1];
    if((A[i][1]-1)/2*K>minsol) minsol=(A[i][1]-1)/2*K;//proxeiro min : m toulaxiston toso oses max aithseis*K
    if(dist(A[i][0]+K*(A[i][1]-1),maxspot)>maxsol) maxsol=dist(A[i][0]+K*(A[i][1]-1),maxspot);//proxeiro max : m to poly na arxisw apo 0 kai na ta balw ola
  }
  ulong sol=quickselect(minsol,maxsol);
  if(sol%2==0) cout<<sol/2<<".00"<<endl;
  else cout<<sol/2<<".50"<<endl;
  return 0;
}
