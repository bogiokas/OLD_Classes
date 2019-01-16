#include<iostream>
#include<algorithm>
#include<cmath>

using namespace std;

int N,M,K;

struct edgetov {//edge to v
  int v;
  int time;
}nullentry={0,0};

struct chainofedges {//element of the neighbourhood
  edgetov e;
  chainofedges* prev;
  chainofedges* next;
};

chainofedges* makechain(int v,int time) {//construct chainofedges
  edgetov edge={v,time};
  chainofedges* output=new chainofedges;
  output->e=edge;
  return output;
}

chainofedges* neighbours[300001];//main array of the graph
void setneighbour(int u,chainofedges* chain) {//add a neighbour
  chainofedges* nscan;
  nscan=neighbours[u];
  if(nscan==NULL) neighbours[u]=chain;
  else {
    while(nscan->next!=NULL) nscan=nscan->next;
    nscan->next=chain;
    chain->prev=nscan;
  }
}

int spanningtree[300001];//a maximum spanning tree
int spanningsize;//tree size <= N-connectedcomponents
bool visited[300001];//flagging of the visited nodes
int connectedcomponents;

struct heapnode {//element of the heap
  edgetov e;
  heapnode* parent;
  heapnode* left;
  heapnode* right;
};

class heap {//each heap contains all edges of a cut of the graph
  heapnode* root;
  heapnode* last;
  private:
    bool less(heapnode* a,heapnode* b) {//comparing of the edges
      if(a->e.time<b->e.time) return true;
      else return false;
    }
    heapnode* biggestchild(heapnode* a) {//returns NULL if no child
      if(a->right==NULL||less(a->right,a->left)) return a->left;
      else return a->right;
    }
    void appendnode(heapnode* newelement) {//appends a node at a new "last" position
      if(last==NULL) {//if heap is empty, then the new element is the root
        root=newelement;
        last=root;
      }
      else {//else, go up until you can turn right or until you reach root
        while(last->parent!=NULL&&last->parent->right==last) last=last->parent;
        if(last->parent==NULL) {//if you reached root, then the height has increazed by one and the new "last" is at the bottom left
          while(last->left!=NULL) last=last->left;
          last->left=newelement;
          newelement->parent=last;
          last=newelement;
        }
        else {//else try to turn right
          last=last->parent;
          if(last->right==NULL) {
            last->right=newelement;
            newelement->parent=last;
            last=newelement;
          }
          else {
            last=last->right;
            while(last->left!=NULL) last=last->left;//and then continue left, til the bottom
            last->left=newelement;
            newelement->parent=last;
            last=newelement;
          }
        }
      }
    }
    void detachnode() {//detaches a node from the "last" position (and finds the new "last")
      if(last->parent==NULL) {//if last=root, then the resulting heap is empty
        delete last;
        last=NULL;
      }
      else {//else,go one step up (in order to delete the node)
        last=last->parent;
        if(last->right!=NULL) {//if you can turn left, then do so and name this the new "last"
          delete last->right;
          last->right=NULL;
          last=last->left;
        }
        else {//else, go up until you can turn left, or you reach root
          delete last->left;
          last->left=NULL;
          while(last->parent!=NULL&&last->parent->left==last) last=last->parent;
          if(last->parent==NULL) while(last->right!=NULL) last=last->right;//if you reach root, then the height has decreased by one and the new "last" is at the bottom right
          else {//else try to turn left
            last=last->parent;
            if(last->left!=NULL) {
              last=last->left;
              while(last->right!=NULL) last=last->right;//end then continue right til the bottom
            }
          }
        }
      }
    }
    void bubbleup() {//if current>parent, swap, forall "current" beginning from "last"
      heapnode* scanheap=last;
      while(scanheap->parent!=NULL&&less(scanheap->parent,scanheap)) {
        heapnode foo;
        foo.e=scanheap->parent->e;
        scanheap->parent->e=scanheap->e;
        scanheap->e=foo.e;
        scanheap=scanheap->parent;
      }
    }
    void bubbledown() {//if current<child, swap, forall "current" beginning from "root"
      heapnode* scanheap=root;
      heapnode* child=biggestchild(scanheap);
      while(child!=NULL&&less(scanheap,child)) {
        heapnode foo;
        foo.e=child->e;
        child->e=scanheap->e;
        scanheap->e=foo.e;
        scanheap=child;
        child=biggestchild(scanheap);
      }
    }
  public:
    heap() {//constructor
      root=NULL;
      last=root;
    }
    void insert(edgetov entry) {//insert a new node at position "last+1" and then bubbleup
      heapnode* newelement=new heapnode;
      newelement->e=entry;
      appendnode(newelement);
      bubbleup();
    }
    edgetov remove() {//remove the root (biggest node), replace it with the node from "last" and then find new last and bubbledown
      edgetov output=root->e;
      root->e=last->e;
      detachnode();
      bubbledown();
      return output;
    }
    bool isempty() {//equiv root==NULL
      return last==NULL;
    }
};


void addneighbourstoheap(int u,heap* A) {//adds all (u,v) into A, if v has not been visited
  chainofedges* chain=neighbours[u];
  while(chain!=NULL) {
    if(!visited[chain->e.v]) A->insert(chain->e);
    chain=chain->next;
  }
}

void prim(heap concom) {//Prim's algorithm -> maximum spanning tree
  while(!concom.isempty()&&spanningsize<N-connectedcomponents) {
    edgetov e=concom.remove();
  if(!visited[e.v]) {
    visited[e.v]=true;
    spanningtree[++spanningsize]=e.time;
    addneighbourstoheap(e.v,&concom);
    }
  }
}

int main() {
  cin>>N>>M>>K;
  int vertex,vertey;
  int edgetime;
  for(int i=1;i<=M;i++) {
    cin>>vertex>>vertey>>edgetime;
    chainofedges* nofx=makechain(vertey,edgetime);//neighbour of x
    chainofedges* nofy=makechain(vertex,edgetime);//neighbour of y
    setneighbour(vertex,nofx);
    setneighbour(vertey,nofy);
  }
  spanningsize=0;
  connectedcomponents=0;
  for(int i=1;i<=N;i++) {
    if(!visited[i]) {
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
  if(spanningsize<=K) cout<<"infinity"<<endl;
  else cout<<spanningtree[K+1]<<endl;
  return 0;
}
