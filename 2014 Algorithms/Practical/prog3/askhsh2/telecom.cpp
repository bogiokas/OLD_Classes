#include<iostream>

using namespace std;

int N;

struct edge {
  int u;
  int v;
  int c;
}

struct chain {
  edge e;
  chain* next;
  chain* prev;
}

struct bag {
  edge e;
  bag* parent;
  bag* left;
  bag* right;
  bag* head;
}

class edgedecomposition {
  bag* root;














int main() {











  return 0;
}
