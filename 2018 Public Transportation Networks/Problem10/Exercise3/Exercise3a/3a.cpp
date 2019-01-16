#include<iostream>
#include<vector>

using namespace std;

const int BIG = 1000; //BIG = infty
const int N = 7; //nodes of G
const int graph[N][N] = { //adj. matrix of G
	{  0, -1, -1, 15, 12, -1, -1},
	{ -1,  0, 15, -1, 13, 10, -1},
	{ -1, 15,  0, -1, -1, -1, 10},
	{ 15, -1, -1,  0, -1, -1, 12},
	{ 12, 13, -1, -1,  0,  8,  9},
	{ -1, 10, -1, -1,  8,  0, 10},
	{ -1, -1, 10, 12,  9, 10,  0}
};

int min(int a, int b) {
	if(a<=b) return a;
	else return b;
}

void print2dV(vector<vector<int>> input) { //only good aligned for integer values in [0,99]
	int n = input.size();
	for(int i=0; i<n; i++) {
		cout<<(char)(65+i)<<" ";
		int m = input[i].size();
		for(int j=0; j<m; j++) {
			if(input[i][j]<10) cout<<" "<<input[i][j]<<" ";
			else cout<<input[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
}

vector<vector<int>> shortest_paths() { //Floyd-Warshall -- also working for digraphs
	//current dist function
	vector<vector<int>>* dist = new vector<vector<int>>(N,vector<int>(N,BIG)); //initialize every distance to oo
	for(int i=0; i<N; i++) {
		for(int j=0; j<N; j++) {
			if(graph[i][j] >= 0) (*dist)[i][j] = graph[i][j]; //initialize any distance of some (u,v) to c(u,v)
		}
	}
	//update dist on each iteration, using {0,..,k} as intermediate vertices
	for(int k=0; k<N; k++) {
		vector<vector<int>>* temp = new vector<vector<int>>(N,vector<int>(N)); //new distances saved temporary
		for(int i=0; i<N; i++) {
			for(int j=0; j<N; j++) {
				(*temp)[i][j] = min((*dist)[i][j],(*dist)[i][k]+(*dist)[k][j]); //update according to the dyn. prog. relation
			}
		}
		delete dist;
		dist = temp; //new distances
	}
	return *dist;
}

struct edge { //e=(u,v), d=c(u,v) -- digraph edges
	int u;
	int v;
	int d;
	edge(int u, int v, int d) {
		this->u = u;
		this->v = v;
		this->d = d;
	}
};
inline bool operator==(const edge& lhs, const edge& rhs) {return lhs.u==rhs.u && lhs.v==rhs.v && lhs.d==rhs.d;} //probably not needed
inline bool operator!=(const edge& lhs, const edge& rhs) {return !(lhs==rhs);} //this neither
inline bool operator< (const edge& lhs, const edge& rhs) {return lhs.d<rhs.d;} //in order for our heap to rank them
inline bool operator> (const edge& lhs, const edge& rhs) {return rhs<lhs;} //just in case
inline bool operator<=(const edge& lhs, const edge& rhs) {return !(lhs>rhs);} //just the same
inline bool operator>=(const edge& lhs, const edge& rhs) {return !(lhs<rhs);} // -- the most important code line

template <class T> //why not build it general
class binary_heap_min { //a binary heap with minimum at the top
	private:
	vector<T>* elements; //main db
	void swap(int i, int j) { //swap elements at places i,j
		T tmp=(*elements)[i];
		(*elements)[i]=(*elements)[j];
		(*elements)[j]=tmp;
	}
	int argmin(int i, int j) { //return the place having the smallest element, between i,j
		if((*elements)[i]<=(*elements)[j]) return i;
		else return j;
	}

	void bubbleUp(int i) { //main up-move of the heap
		if(i>0) {
			int p = (i-1)/2; //parent -- may not exist
			if((*elements)[p]>(*elements)[i]) swap(p,i);
			bubbleUp(p);
		}
	}
	void bubbleDown(int i) { //main down-move of the heap
		int l = 2*i+1; //left child
		int r = 2*i+2; //right child
		int n = elements->size();
		int c; //smallest child -- may not exist
		if(l <= n) {
			if(r <= n) c = argmin(l,r);
			else c = l;
			if((*elements)[i]>(*elements)[c]) swap(i,c);
			bubbleDown(c);
		}
	}

	public:
	binary_heap_min() {
		this->elements = new vector<T>;
	}
	~binary_heap_min() {
		delete this->elements;
	}
//main heap functions
	void push(T elt) {
		elements->push_back(elt);
		bubbleUp(elements->size()-1);
	}
	T pop() {
		T result = (*elements)[0];
		(*elements)[0] = (*elements)[elements->size()-1];
		elements->pop_back();
		bubbleDown(0);
		return result;
	}
	bool isEmpty() {
		return elements->size()==0;
	}
//just a print function -- each level in a line
	void print() {
		cout<<"heap:"<<endl;
		int max_elts_in_floor = 1;
		int rem_elts_in_floor = 1;
		for(int i=0;i<elements->size();i++) {
			cout<<(*elements)[i]<<" ";
			rem_elts_in_floor--;
			if(rem_elts_in_floor==0) {
				cout<<endl;
				max_elts_in_floor *= 2;
				rem_elts_in_floor = max_elts_in_floor;
			}
		}
		if(rem_elts_in_floor < max_elts_in_floor) cout<<endl;
	}
};

class mwSTBuilder {//Prim -- used class instead of function, b/c I needed some global vector vars and a separate examine function
	private:
	vector<vector<int>>* dist; //I suppose int distances
	string listOfLabels;
	int V; //actually, |V(G)|
	vector<edge>* mwst; //Mehrwertsteuer
	binary_heap_min<edge>* outedges; //used only by Prim
	vector<bool>* isExamined; //used only by Prim
	void examine(int u) {
		for(int v=0;v<dist->size();v++) {
			if(v!=u) { //we don't like loops
				int d = (*dist)[u][v];
				edge e(u,v,d);
				outedges->push(e); //examine later
			}
		}
		(*isExamined)[u] = true;
	}
	public:
	mwSTBuilder(vector<vector<int>>* dist, string listOfLabels) { //solved when first defined
		this->dist = dist;
		this->listOfLabels = listOfLabels; //in order to easily follow what vertices of the graph are still in -- can be implemented better
		this->V = dist->size();
		this->mwst = new vector<edge>;
		this->outedges = new binary_heap_min<edge>;
		this->isExamined = new vector<bool>(V,false);
		examine(0); //initialize to an arbitrary vertex
		while(!outedges->isEmpty()) { //we still have to examine edges -- actually there are better stop constrains, but N=7
			edge e = outedges->pop(); 
			if(!(*isExamined)[e.v]) { //found new
				mwst->push_back(e);
				examine(e.v);
			}
		}
		delete outedges; //cleanup
		delete isExamined;
	}
	~mwSTBuilder() {
		delete mwst;
	}
//needed functions
	vector<edge> get() {
		return *mwst;
	}
	int cost() {
		int sum = 0;
		for(int i=0;i<mwst->size();i++) sum += (*mwst)[i].d;
		return sum;
	}
	void print() {
		for(int i=0;i<mwst->size();i++) {
			edge e = (*mwst)[i];
			char u_name = listOfLabels[e.u];
			char v_name = listOfLabels[e.v];
			cout<<u_name<<"-"<<v_name<<": "<<e.d<<endl;
		}
	}
};

int main() {
	//define Kn with shortest path distances
	vector<vector<int>> metricClosure = shortest_paths();
	cout<<"Shortest path table: "<<endl;
	cout<<"   A  B  C  D  E  F  G"<<endl;
	print2dV(metricClosure);
	cout<<endl;
	//the MWST of the closure, with E
	mwSTBuilder withE(&metricClosure,"ABCDEFG");
	cout<<"With E: "<<withE.cost()<<endl;
	withE.print();
	cout<<endl;
	//the MWST of the closure, without E
	vector<vector<int>> metricClosureWithoutE(N-1);
	for(int i=0;i<N;i++) {
		if(i < 4) {
			for(int j=0; j<N; j++) {
				if(j != 4) metricClosureWithoutE[i].push_back(metricClosure[i][j]);
			}
		}
		else if(i > 4) {
			for(int j=0; j<N; j++) {
				if(j != 4) metricClosureWithoutE[i-1].push_back(metricClosure[i][j]);
			}
		}
	}
	mwSTBuilder withoutE(&metricClosureWithoutE,"ABCDFG");
	cout<<"Without E: "<<withoutE.cost()<<endl;
	withoutE.print();
	return 0;
}
