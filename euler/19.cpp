#include <iostream>
#include <cstdlib>

using namespace std;

inline bool isFirstOfM(int n,int leap[],int nleap[]);
bool isLeap(int n);
int getYin(int n);
int getYdays(int y);

int main(int argc,char *argv[]){
	int leapD[12] = {0};
	leapD[0] = 1;
	leapD[1] = leapD[0] + 31;
	leapD[2] = leapD[1] + 29;
	leapD[3] = leapD[2] + 31;
	leapD[4] = leapD[3] + 30;
	leapD[5] = leapD[4] + 31;
	leapD[6] = leapD[5] + 30;
	leapD[7] = leapD[6] + 31;
	leapD[8] = leapD[7] + 31;
	leapD[9] = leapD[8] + 30;
	leapD[10] = leapD[9] + 31;
	leapD[11] = leapD[10] + 30;

	int nLeapD[12] = {0};
	nLeapD[0] = 1;
	nLeapD[1] = nLeapD[0] + 31;
	nLeapD[2] = nLeapD[1] + 28;
	nLeapD[3] = nLeapD[2] + 31;
	nLeapD[4] = nLeapD[3] + 30;
	nLeapD[5] = nLeapD[4] + 31;
	nLeapD[6] = nLeapD[5] + 30;
	nLeapD[7] = nLeapD[6] + 31;
	nLeapD[8] = nLeapD[7] + 31;
	nLeapD[9] = nLeapD[8] + 30;
	nLeapD[10] = nLeapD[9] + 31;
	nLeapD[11] = nLeapD[10] + 30;
	int day = 0;
	int num = 0;
	int maxDays = 0;
	for(int c = 1901; c < 2001; c++){
		maxDays += isLeap(c) ? 366 : 365;
	}

	while(1){

		if(isFirstOfM(day,leapD,nLeapD)){
			num++;
		}
		day += 1;
		if(day >= maxDays ) break;
	}
	cout<<endl<<"res:"<<num;
	return 0;
}

bool isLeap(int n){
	return ( n % 400 == 0 || ( n % 100 != 0 && n % 4 == 0) );
}

inline bool isFirstOfM(int n,int leap[],int nleap[]){
	if( n % 7 != 0) return false;
	int y = getYin(n);

	n -= getYdays(y);
	if(isLeap(y)){
		for(int c = 0; c < 12; c++) if(n == leap[c]) return true;
		return false;
	}else{
		for(int c = 0; c < 12; c++) if(n == nleap[c]) return true;

		return false;
	}
}

int getYdays(int y){
	int d = 0;
	while(y != 1900){
		d += isLeap(y) ? 366 : 365;
		y--;
	}
	return d;
}

int getYin(int n){
	int y = 1900;
	while(n > 365){
		n -= isLeap(y) ? 366 : 365;
		y++;
	}

	return y;
}
