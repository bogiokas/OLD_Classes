#include<iostream>
#include <algorithm>
#include<cmath>

using namespace std;

struct edgetov {
  int v;
  int time;
}nullentry={0,0};

struct chainofedges {
  edgetov e;
  chainofedges* prev;
  chainofedges* next;
};

chainofedges* makechain(int v,int time) {
  edgetov edge={v,time};
  chainofedges* output=new chainofedges;
  output->e=edge;
  return output;
}

int N,M,K;

chainofedges* neighbours[300001];
void setneighbour(int u,chainofedges* chain) {
  chainofedges* nscan;
  nscan=neighbours[u];
  if(nscan==NULL) neighbours[u]=chain;
  else {
    while(nscan->next!=NULL) nscan=nscan->next;
    nscan->next=chain;
    chain->prev=nscan;
  }
}

int spanningtree[300001];
int spanningsize;
bool visited[300001];
int connectedcomponents;

class heap {
  edgetov base[300002];
  int heapsize;
  private:
    int maxentry(int i,int j) {
      if(base[i].time>base[j].time) return i;
      else return j;
    }
    void bubbleup() {
      int scanheap=heapsize;
//cout<<scanheap/2<<" "<<scanheap<<" "<<base[scanheap/2].time<<" "<<base[scanheap].time<<"???????"<<endl;
      while(scanheap/2>0&&base[scanheap/2].time<base[scanheap].time) {
//cout<<scanheap/2<<" "<<scanheap<<" "<<base[scanheap/2].time<<" "<<base[scanheap].time<<"!!!!!!!!"<<endl;
        edgetov foo=base[scanheap/2];
        base[scanheap/2]=base[scanheap];
        base[scanheap]=foo;
        scanheap/=2;
      }
    }
    void bubbledown() {
      int scanheap=1;
//cout<<scanheap*2<<" "<<scanheap<<" "<<base[scanheap].time<<" "<<base[scanheap].time<<"???????"<<endl;
      while(2*scanheap<=heapsize&&base[maxentry(2*scanheap,2*scanheap+1)].time>base[scanheap].time) {
        int i=maxentry(2*scanheap,2*scanheap+1);
//cout<<i<<" "<<scanheap<<" "<<base[i].time<<" "<<base[scanheap].time<<"!!!!!!!!"<<endl;
//cout<<i<<":: -"<<base[i].v<<":"<<base[i].time<<endl;
        edgetov foo=base[i];
        base[i]=base[scanheap];
        base[scanheap]=foo;
        scanheap=i;
      }
//      base[heapsize]=nullentry;
    }
  public:
    heap() {
      heapsize=0;
      for(int i=0;i<=300001;i++) base[i]=nullentry;
    }
    void insert(edgetov entry) {
      heapsize++;
//cout<<heapsize<<endl;
      base[heapsize]=entry;
      bubbleup();
    }
    edgetov remove() {
      edgetov output=base[1];
      base[1]=base[heapsize];
      base[heapsize]=nullentry;
      heapsize--;
//printheap();
      bubbledown();
      return output;
    }
    bool isempty() {
//cout<<"heapsize:"<<heapsize<<endl;
      return heapsize==0;
    }
    int size() {
      return heapsize;
    }
    void printheap() {
      cout<<"Spanning tree: ";
      for(int i=1;i<=spanningsize;i++) cout<<spanningtree[i]<<" ";
      cout<<endl;
      int m=1;
      cout<<"     HEAP"<<endl;
      for(int i=1;i<=heapsize;i++) {
        cout<<"   -"<<base[i].v<<":"<<base[i].time<<" ";
        if(i==pow(2,m)-1) {
          cout<<endl;
          m++;
        }
      }
      cout<<endl<<endl;
    }
};


void addneighbourstoheap(int u,heap* A) {
  chainofedges* chain=neighbours[u];
  while(chain!=NULL) {
//cout<<"edw"<<endl;
    if(!visited[chain->e.v]) A->insert(chain->e);
    chain=chain->next;
  }
}

void prim(heap concom) {
  while(!concom.isempty()&&spanningsize<N-connectedcomponents) {
//concom.printheap();
    edgetov e=concom.remove();
//cout<<e.v<<" "<<e.time<<endl;
//concom.printheap();
  if(!visited[e.v]) {
//cout<<e.v<<" "<<e.time<<endl;
    visited[e.v]=true;
    spanningtree[++spanningsize]=e.time;
    addneighbourstoheap(e.v,&concom);
//concom.printheap();
    }
  }
}

void printedges() {
  for(int i=1;i<=N;i++) {
    chainofedges* foo=neighbours[i];
    while(foo!=NULL) {
      cout<<i<<" "<<foo->e.v<<" "<<foo->e.time<<" "<<endl;
      foo=foo->next;
    }
  }
}

int main() {
  cin>>N>>M>>K;
//  cout<<"lala"<<endl;
  int vertex,vertey;
  int edgetime;
  for(int i=1;i<=M;i++) {
    cin>>vertex>>vertey>>edgetime;
    chainofedges* nofx=makechain(vertey,edgetime);//neighbour of x
    chainofedges* nofy=makechain(vertex,edgetime);//neighbour of y
    setneighbour(vertex,nofx);
    setneighbour(vertey,nofy);
  }
//  printedges();
cout<<"telos"<<endl;
  spanningsize=0;
  connectedcomponents=0;
  for(int i=1;i<=N;i++) {
//cout<<"!"<<endl;
    if(!visited[i]) {
//cout<<"?????????"<<endl;
      connectedcomponents++;
      visited[i]=true;
      if(neighbours[i]!=NULL) {
        heap cut=heap();
        addneighbourstoheap(i,&cut);
        prim(cut);
      }
    }
  }
  sort(&spanningtree[1],&spanningtree[spanningsize+1]);
/*  for(int i=1;i<=spanningsize;i++) {
    cout<<spanningtree[i]<<endl;
  }*/
  if(spanningsize<=K) cout<<"infinity"<<endl;
  else cout<<spanningtree[K+1]<<endl;
  return 0;
}
