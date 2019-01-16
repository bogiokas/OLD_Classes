#include<iostream>
#include<vector>
#include<string>

using namespace std;

const int N = 7; //nodes
const int L = 7; //lines
const string lines[L] = {"AD", "AEB", "AEF", "DGC", "GEBF", "BCGF", "DGF"};
const int D = 6; //demands
const string dV[D] = {"AB", "AF", "DC", "DF", "GB", "CA"};
const int    dX[D] = { 50 ,  50 ,  80 ,  20 ,  40 ,  30 };
const int C = 50; //capacity
const int fmin = 0;
const int fmax = 2;

int l2n(char label) { //label to name -- labels are consequtive capital letters begining with A
	return (int)label - 65;
}
char n2l(int name) {
	return (char)(name+65);
}

struct edge {
	int u;
	int v;
	int line;
	edge() {
	}
	edge(int u, int v, int line) {
		this->u = u;
		this->v = v;
		this->line = line;
	}
	void print() {
		cout<<n2l(u)<<n2l(v)<<line;
	}
};

struct demand {
	int s;
	int t;
	int num;
	demand() {
	}
	demand(int s, int t, int num) {
		this->s = s;
		this->t = t;
		this->num = num;
	}
	void print() {
		cout<<n2l(s)<<n2l(t);
	}
};

void x(demand d, edge e) { //prints var x_{ST,e} as xST_uvl
	cout<<"x";
	d.print();
	cout<<"_";
	e.print();
}

void f(int l) { //prints var f_l as fl
	cout<<"f"<<l;
}

int main() {
//Define Edges
	vector<edge> Edges;
	for(int l=0; l<L; l++) { //all lines forward, from 1 to L
		for(int s=0; s<lines[l].length()-1; s++) {
			int uname = l2n(lines[l][s]);
			int vname = l2n(lines[l][s+1]);
			Edges.push_back(edge(uname,vname,l+1));
		}
	}
	for(int l=0; l<L; l++) { //alll lines backward, from L+1 to 2L
		for(int s=lines[l].length()-1; s>0; s--) {
			int uname = l2n(lines[l][s]);
			int vname = l2n(lines[l][s-1]);
			Edges.push_back(edge(uname,vname,l+1+L));
		}
	}
	int M = Edges.size();
//Define Demands
	vector<demand> Demands(D);
	for(int d=0; d<D; d++) {
		int sname = l2n(dV[d][0]);
		int tname = l2n(dV[d][1]);
		int value = dX[d];
		Demands[d] = demand(sname,tname,value);
	}
//Define A
	vector<vector<int>> A(N,vector<int>(M,0));
	for(int i=0; i<N; i++) {
		for(int j=0; j<M; j++) {
			if(Edges[j].u == i) A[i][j] = -1;
			else if(Edges[j].v == i) A[i][j] = 1;
		}
	}

// --- MIP ---
	cout<<"Minimize"<<endl;
	// number of lines used (???)
	for(int l=1; l<=2*L; l++) {
		if(l>1) cout<<" + ";
		f(l);
	}
	cout<<endl<<endl;

	cout<<"Subject To"<<endl;
	// Capacities not exceeded
	for(int j=0; j<M; j++) {
		for(int k=0; k<D; k++) {
			if(k>0) cout<<" + ";
			x(Demands[k], Edges[j]);
		}
		cout<<" - "<<C;
		f(Edges[j].line);
		cout<<" <= 0"<<endl;
	}
	// People get transfered (Ax=b)
	for(int k=0; k<D; k++) {
		for(int i=0; i<N; i++) {
			for(int j=0; j<M; j++) {
				if(A[i][j] != 0) {
					if(A[i][j] > 0) cout<<" + ";
					else if(A[i][j] < 0) cout<<" - ";
					x(Demands[k],Edges[j]);
				}
			}
			cout<<" = ";
			if(i == Demands[k].s) cout<<" - "<<Demands[k].num;
			else if(i == Demands[k].t) cout<<Demands[k].num;
			else cout<<0;
			cout<<endl;
		}
	}
	cout<<endl;
	cout<<"Bounds"<<endl;
	// Do not overuse lines
	for(int l=1; l<2*L; l++) {
		cout<<fmin<<" <= ";
		f(l);
		cout<<" <= "<<fmax<<endl;
	}
	// only positive transfers
	for(int k=0; k<D; k++) {
		for(int j=0; j<M; j++) {
			x(Demands[k], Edges[j]);
			cout<<" >= "<<0;
			cout<<endl;
		}
	}
	cout<<endl;
	cout<<"General"<<endl;
	//fl integer
	for(int l=1; l<=2*L; l++) {
		f(l);
		cout<<endl;
	}
	cout<<endl;
	cout<<"End";
	return 0;
}
