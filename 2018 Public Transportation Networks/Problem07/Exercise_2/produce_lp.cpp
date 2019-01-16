#include<iostream>
#include<vector>
#include<map>
#include<stack>

using namespace std;
struct network {
	int nodes;
	int lines;
	vector<vector<int>> stops;
	vector<vector<int>> times;
	vector<pair<int,int>> lines_through_node(int n) { //returns a list of every (line,stop) through node n -- TODO change datastructure to make it efficient
		vector<pair<int,int>> result;
		for(int l=0;l<lines;l++) {
			for(int s=0;s<stops[l].size();s++) {
				if(stops[l][s] == n) result.push_back(make_pair(l,s));
			}
		}
		return result;
	}
	friend ostream& operator<<(ostream& o, const network& N) {
		o<<"Network with "<<N.nodes<<" Stations, "<<N.lines<<" Lines"<<endl;
		for(int l=0;l<N.lines;l++) {
			for(int s=0;s<N.stops[l].size();s++) {
				o<<"["<<N.stops[l][s]<<"]";
				if(s<N.stops[l].size()-1) o<<"--"<<N.times[l][s]<<"--";
				else o<<endl;
			}
		}
		return o;
	}
};

struct event {
	int line;
	char direction; // ')' | '('
	int stop;
	char action; // 'a'rrival | 'd'eparture
	event() {
	}
	event(int line, char direction, int stop, char action) {
		this->line = line;
		this->direction = direction;
		this->stop = stop;
		this->action = action;
	}
	bool operator>(const event e) const {
		return tie(line,direction,stop,action) > tie(e.line,e.direction,e.stop,e.action);
	}
	bool operator<(const event e) const {
		return tie(line,direction,stop,action) < tie(e.line,e.direction,e.stop,e.action);
	}
	bool operator==(const event e) const {
		return tie(line,direction,stop,action) == tie(e.line,e.direction,e.stop,e.action);
	}
	bool operator!=(const event e) const {
		return tie(line,direction,stop,action) != tie(e.line,e.direction,e.stop,e.action);
	}
	friend ostream& operator<<(ostream& o, const event& e) {
		o<<"X"<<e.line<<e.direction<<e.stop<<e.action;
		return o;
	}
};

struct activity{
	event from;
	event to;
	char type; // 'd'riving | 'w'aiting | 't'ransfer
	int l;
	int u;
	activity() {
	}
	activity(event from,event to,char type,int l,int u) {
		this->from = from;
		this->to = to;
		this->type = type;
		this->l = l;
		this->u = u;
	}
	bool operator<(const activity a) const {
		return tie(from,to) < tie(a.from,a.to);
	}
	friend ostream& operator<<(ostream& o, const activity& a) {
		o<<a.from<<"_"<<a.to;
		return o;
	}
};

class pesp {
	public:
	int T,num_e,num_a;
	map<event,vector<activity>*> activities;
	activity edge(event u,event v) {
		for(int i=0;i<activities[u]->size();i++) {
			if(v == (*activities[u])[i].to) return (*activities[u])[i];
		}
	}
	friend ostream& operator<<(ostream& o, pesp& E) {
		cout<<"PESP with "<<E.num_e<<" events, "<<E.num_a<<" activities and T="<<E.T<<endl;
		map<event,vector<activity>*>::iterator it = E.activities.begin();
		while(it != E.activities.end()) {
			event tmp = it->first;
			cout<<tmp<<":"<<endl;
			vector<activity>* tmpact = it->second;
			for(int i=0;i<tmpact->size();i++) {
				activity edge = (*tmpact)[i];
				cout<<"\t"<<edge<<endl;
			}
			it++;
		}
		return o;
	}
};

struct cycle {
	map<activity,int> data;
	cycle() {
	}
	cycle(pesp* E) {
		map<event,vector<activity>*>::iterator it = E->activities.begin();
		while(it != E->activities.end()) {
			vector<activity>* list = it->second;
			for(int i=0;i<list->size();i++) {
				data.insert(make_pair((*list)[i],0));
			}
			it++;
		}
	}
	int low() {
		int result = 0;
		map<activity,int>::iterator it = data.begin();
		while(it != data.end()) {
			result+=it->second*it->first.l;
			it++;
		}
		return result;
	}
	friend ostream& operator<<(ostream& o, cycle& a) {
		bool isfirst = true;
		map<activity,int>::iterator it = a.data.begin();
		while(it != a.data.end()) {
			if(it->second == -1) {
				o<<"- "<<it->first<<" ";
				isfirst=false;
			}
			else if(it->second == 1) {
				if(isfirst) o<<it->first<<" ";
				else o<<"+ "<<it->first<<" ";
				isfirst=false;
			}
			it++;
		}
		return o;
	}
};

int main() {
	network* N = new network();
	int n,L; // n = #stops, L = #lines
	cin>>n>>L;
	N->nodes = n;
	N->lines = L;
	for(int l=0;l<L;l++) {
		int s;
		cin>>s;
		vector<int> stoplist(s);
		for(int i=0;i<s;i++) cin>>stoplist[i];
		vector<int> timelist(s-1);
		for(int i=0;i<s-1;i++) cin>>timelist[i];
		N->stops.push_back(stoplist);
		N->times.push_back(timelist);
	}

	pesp* E = new pesp();
	int T;
	cin>>T;
	E->T = T;
	// add events
	E->num_e = 0;
	for(int l=0;l<L;l++) {
		int num_s = N->stops[l].size();
		for(int s=0;s<num_s;s++) {
			if(s>0) {
				E->activities.insert(make_pair(event(l,')',s,'a'),new vector<activity>));
				E->activities.insert(make_pair(event(l,'(',s,'a'),new vector<activity>));
				E->num_e +=2;
			}
			if(s<num_s-1) {
				E->activities.insert(make_pair(event(l,')',s,'d'),new vector<activity>));
				E->activities.insert(make_pair(event(l,'(',s,'d'),new vector<activity>));
				E->num_e+=2;
			}
		}
	}
	int wl,wu,tl,tu;
	cin>>wl>>wu>>tl>>tu;
	// add activities
	E->num_a = 0;
	for(int l=0;l<L;l++) {
		int num_s = N->stops[l].size();
		for(int s=0;s<num_s;s++) {
			event from,to;
			if(s<num_s-1) {
				from = event(l,')',s,'d'); //driving in ) direction
				to = event(l,')',s+1,'a');
				E->activities[from]->push_back(activity(from,to,'d',N->times[l][s],N->times[l][s]));
				from = event(l,'(',s,'d'); //driving in ( direction
				to = event(l,'(',s+1,'a');
				E->activities[from]->push_back(activity(from,to,'d',N->times[l][num_s-1-(s+1)],N->times[l][num_s-1-(s+1)]));
				E->num_a+=2;
			}
			if(s>0 && s<num_s-1) {
				from = event(l,')',s,'a'); //waiting in ) direction
				to = event(l,')',s,'d');
				E->activities[from]->push_back(activity(from,to,'w',wl,wu));
				from = event(l,'(',s,'a'); //waiting in ( direction
				to = event(l,'(',s,'d');
				E->activities[from]->push_back(activity(from,to,'w',wl,wu));
				E->num_a+=2;
			}
			vector<pair<int,int>> otherlines = N->lines_through_node(N->stops[l][s]);
			for(int i=0;i<otherlines.size();i++) { //transfer activities
				int otherl = otherlines[i].first;
				int others = otherlines[i].second;
				int othernum_s = N->stops[otherl].size();
				if(s > 0 && others < othernum_s-1 && otherl != l) {
					from = event(l,')',s,'a');
					to = event(otherl,')',others,'d');
					E->activities[from]->push_back(activity(from,to,'t',tl,tu));
					E->num_a+=1;
				}
				if(s > 0 && others > 0) {
					from = event(l,')',s,'a');
					to = event(otherl,'(',othernum_s-1 - others,'d');
					E->activities[from]->push_back(activity(from,to,'t',tl,tu));
					E->num_a+=1;
				}
				if(s < num_s-1 && others > 0 && otherl != l) {
					from = event(l,'(',num_s-1 - s,'a');
					to = event(otherl,'(',othernum_s-1 - others,'d');
					E->activities[from]->push_back(activity(from,to,'t',tl,tu));
					E->num_a+=1;
				}
				if(s < num_s-1 && others < othernum_s-1) {
					from = event(l,'(',num_s-1 - s,'a');
					to = event(otherl,')',others,'d');
					E->activities[from]->push_back(activity(from,to,'t',tl,tu));
					E->num_a+=1;
				}
			}
		}
	}

	vector<activity> edges;
	map<event,vector<activity>*>::iterator ite = E->activities.begin();
	while(ite != E->activities.end()) {
		vector<activity>* list = ite->second;
		for(int i=0;i<list->size();i++) edges.push_back((*list)[i]);
		ite++;
	}

	//DFS
	stack<pair<event,event>> DFS; //first the node, second the wannabe parent
	map<event,event> DFSparent;
	map<event,bool> DFSseen;
	vector<cycle> CycleBasis;

	map<event,vector<activity>*>::iterator it = E->activities.begin(); //initialize the maps
	while(it != E->activities.end()) {
		event tmp = it->first;
		DFSparent.insert(make_pair(tmp,tmp));
		DFSseen.insert(make_pair(tmp,false));
		it++;
	}

	event root = event(0,')',0,'d');
	DFS.push(make_pair(root,root));
	while(!DFS.empty()) {
		event current = DFS.top().first;
		event previous = DFS.top().second;
		DFS.pop();
		if(!DFSseen[current]) {
			DFSseen[current] = true;
			DFSparent[current] = previous;
			vector<activity>* neighb = E->activities[current];
			for(int i=0;i<neighb->size();i++) DFS.push(make_pair((*neighb)[i].to,current));
		}
		else {
			cycle C(E);
			event v,u;
			v = current;
			u = DFSparent[current];
			while(u != root) {
				activity e = E->edge(u,v);
				C.data[e] --;
				v = u;
				u = DFSparent[v];
			}
			v = current;
			u = previous;
			while(u != root) {
				activity e = E->edge(u,v);
				C.data[e] ++;
				v = u;
				u = DFSparent[v];
			}
			CycleBasis.push_back(C);
		}
	}
	cout<<"Minimize"<<endl;
	cout<<edges[0];
	for(int i=1;i<edges.size();i++) cout<<" + "<<edges[i];
	cout<<endl<<endl;
	cout<<"Subject To"<<endl;
	for(int i=0;i<CycleBasis.size();i++) cout<<CycleBasis[i]<<" - "<<T<<"z"<<i<<" = "<<-CycleBasis[i].low()<<endl;
	cout<<endl;
	cout<<"Bounds"<<endl;
	for(int i=0;i<edges.size();i++) cout<<"0 <= "<<edges[i]<<" <= "<<edges[i].u-edges[i].l<<endl;
	for(int i=0;i<CycleBasis.size();i++) cout<<"-inf <= z"<<i<<" <= +inf"<<endl;
	cout<<endl;
	cout<<"General"<<endl;
	for(int i=0;i<CycleBasis.size();i++) cout<<"z"<<i<<endl;
	cout<<endl;
	cout<<"End"<<endl;
	return 0;
}
