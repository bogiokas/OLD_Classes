#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int const mA = 5;
int const nA = 4;

void print(int M[2*mA][2*mA], int N) {
	for(int r=0;r<N;r++) {
		for(int c=0;c<N;c++) {
			cout<<M[r][c]<<" ";
		}
		cout<<endl;
	}
}

int det(int M[2*mA][2*mA], int N) {
	if(N==1) return M[0][0];
	else {
		int res = 0;
		for(int i=0;i<N;i++) {
			if(M[0][i] != 0) {
				int K[2*mA][2*mA];
				for(int r=1;r<N;r++) {
					for(int c=0;c<N;c++) {
						if(c<i) K[r-1][c] = M[r][c];
						else if(c>i) K[r-1][c-1] = M[r][c];
					}
				}
				res += ( 1-2*(i%2) ) * M[0][i] * det(K,N-1);
			}
		}
		return res;
	}
}

vector<vector<int>> choices(vector<int> N, int k) {
	int n = N.size();
	vector<vector<int>> res;
	
	vector<bool> ind(n);
	fill(ind.end()-k,ind.end(),true);

	do {
		vector<int> newline;
		for(int i=0; i<n; i++) {
			if(ind[i]) newline.push_back(N[i]);
		}
		res.push_back(newline);
	} while(next_permutation(ind.begin(),ind.end()));

	return res;
}

int main() {
//	int A[nA][mA] = {
//		{ -1, -1,  0,  0},
//		{  1,  0, -1, -1},
//		{  0,  1,  1,  0},
//		{  0,  0,  0,  1}
//	};
	int A[nA][mA] = {
		{ -1, -1,  0,  0,  0},
		{  1,  0, -1, -1,  0},
		{  0,  1,  1,  0, -1},
		{  0,  0,  0,  1,  1}
	};
//	int A[nA][mA] = {
//		{  1, -1, -1,  0,  0,  0,  0},
//		{  0,  1,  0, -1, -1,  0,  0},
//		{  0,  0,  1,  1,  0, -1,  0},
//		{  0,  0,  0,  0,  1,  1, -1}
//	};
	int Id[mA][mA];
	for(int r=0;r<mA;r++) {
		for(int c=0;c<mA;c++) {
			if(r==c) Id[r][c] = 1;
			else Id[r][c] = 0;
		}
	}

	int M[2*mA][2*mA];
	for(int r=0;r<2*mA;r++) {
		for(int c=0;c<2*mA;c++) {
			M[r][c] = 0;
		}
	}
	vector<int> I;
	for(int i=0;i<mA;i++) I.push_back(i);
	vector<int> Rows;
	for(int i=0;i<2*nA;i++) Rows.push_back(i);

	for(int num=1; num<=2*mA; num++) {
cout<<"num: "<<num<<endl;
		for(int kI=1; kI<=num/2; kI++) {
cout<<"   kI: "<<kI<<endl;
			vector<vector<int>> choiceI = choices(I,kI);
			for(int a=0; a<choiceI.size(); a++) {
				vector<vector<int>> newRows = choices(Rows,num-kI);
				for(int r=0; r<newRows.size(); r++) {
					vector<int> Cols;
					for(int i=0; i<mA; i++) {
						if(find(choiceI[a].begin(),choiceI[a].end(),i) == choiceI[a].end()) {
							Cols.push_back(i);
							Cols.push_back(i+mA);
						}
					}
					sort(Cols.begin(),Cols.end());
					vector<vector<int>> newCols = choices(Cols,num-2*kI);
					for(int c=0; c<newCols.size(); c++) {
						vector<int> choiceCols;
						vector<int> choiceRows;
						for(int i=0; i<kI; i++) {
							choiceCols.push_back(choiceI[a][i]);
							choiceCols.push_back(choiceI[a][i]+mA);
							choiceRows.push_back(choiceI[a][i]+2*nA);
						}
						choiceRows.insert(choiceRows.end(),newRows[r].begin(),newRows[r].end());
						choiceCols.insert(choiceCols.end(),newCols[c].begin(),newCols[c].end());
						sort(choiceRows.begin(),choiceRows.end());
						sort(choiceCols.begin(),choiceCols.end());
						for(int i=0; i<num; i++) {
							for(int j=0; j<num; j++) {
								if(choiceRows[i] < nA) {
									if(choiceCols[j] < mA) M[i][j] = A[choiceRows[i]][choiceCols[j]];
									else M[i][j] = 0;
								}
								else if(choiceRows[i] < 2*nA) {
									if(choiceCols[j] < mA) M[i][j] = 0;
									else M[i][j] = A[choiceRows[i]-nA][choiceCols[j]-mA];
								}
								else {
									if(choiceCols[j] < mA) M[i][j] = Id[choiceRows[i]-2*nA][choiceCols[j]];
									else M[i][j] = Id[choiceRows[i]-2*nA][choiceCols[j]-mA];
								}
							}
						}
						if(det(M,num) != 0 && det(M,num) != 1 && det(M,num) != -1) {
							cout<<"rows: ";
							for(int i=0; i<choiceRows.size(); i++) cout<<choiceRows[i]<<" ";
							cout<<endl;
							cout<<"cols: ";
							for(int i=0; i<choiceCols.size(); i++) cout<<choiceCols[i]<<" ";
							cout<<endl;
							print(M,num);
							cout<<det(M,num)<<endl<<endl;
						}
					}
				}
			}
		}
	}
	return 0;
}
