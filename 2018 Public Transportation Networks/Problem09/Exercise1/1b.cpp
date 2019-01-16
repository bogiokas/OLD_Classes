#include<iostream>

using namespace std;

int perm[120][5];
int w[120];

void put(int t, int l, int n) {
	for(int i=0; i<5; i++) {
		if(perm[t][i] < 0) l--;
		if(l==0) {
			perm[t][i] = n;
			break;
		}
	}
}

int main() {
	string st[6];
	st[0] = "RedLeft";
	st[1] = "RedRight";
	st[2] = "Blue";
	st[3] = "Green";
	st[4] = "Yellow";
	int T[5][5];
	int pA[5];
	int pD[5];
	pA[0] = 7;
	pA[1] = 17;
	pA[2] = 12;
	pA[3] = 1;
	pA[4] = 6;
	pD[0] = 19;
	pD[1] = 9;
	pD[2] = 14;
	pD[3] = 12;
	pD[4] = 6;
	for(int i=0; i<5; i++) {
		for(int j=0; j<5; j++) T[i][j] = (36+pD[j]-pA[i])%20 + 4;
	}

	for(int a=0;a<5;a++) {
		for(int b=0;b<4;b++) {
			for(int c=0;c<3;c++) {
				for(int d=0;d<2;d++) {
					int t = 24*a+6*b+2*c+d;
					for(int l=0;l<5;l++) perm[t][l] = -1;
					put(t,a+1,0);
					put(t,b+1,1);
					put(t,c+1,2);
					put(t,d+1,3);
					put(t,1,4);
				}
			}
		}
	}
	int min = 1000;
	int mint;
	for(int t=0; t<120; t++) {
		w[t] = 0;
		for(int i=0; i<5; i++) w[t] += T[i][perm[t][i]];
		if(w[t] < min) min = w[t];
	}
	cout<<"Minimum weight equals "<<min<<" and the possible matchings are:"<<endl;
	for(int t=0; t<120; t++) {
		if(w[t] == min) {
			for(int i=0; i<5; i++) {
				cout<<st[i]<<"->"<<st[perm[t][i]];
				if(i<4) cout<<", ";
			}
			cout<<endl;
		}
	}
	return 0;
}
