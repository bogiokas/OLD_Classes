#include<iostream>

using namespace std;

int stationslack(int B, int A, int l) {
	//Computes the periodic slack at a station, with
	//A+s : \pi at arrival event above
	//B+s : \pi at arrival event left
	//l   : l   at every transfer activity
	return (18-2*A)%10 + (18+2*A+2*l)%10 + (18-2*B)%10 + (18+2*B+2*l)%10 + 2*( (18-A-B)%10 + (18+A+B+2*l)%10 + (18-A+B+l)%10 + (18+A-B+l)%10 );
}

int slack(int a, int b, int c, int d) {
	//Computes the periodic slack at the stations A,B,C,D, with
	//a+s : \pi at arrival event on the left of A (red line)
	//b+s : \pi at arrival event on the left of D (green line)
	//c+s : \pi at arrival event on the top  of D (blue line)
	//d+s : \pi at arrival event on the top  of A (yellow line)
	return stationslack(a,d,2) + stationslack((a+6)%10,(c+1)%10,0) + stationslack((a+1)%10,(b+1)%10,0) + stationslack(b,c,2);
}

int main() {
	int tmp=0;
	int min=200;
	for(int a=0;a<10;a++) {
		for(int b=0;b<10;b++) {
			for(int c=0;c<10;c++) {
				for(int d=0;d<10;d++) {
					tmp=slack(a,b,c,d);
					if(tmp<min) min = tmp;
				}
			}
		}
	}
	cout<<min<<endl;
	return 0;
}
