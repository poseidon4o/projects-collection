#include <iostream>
#include <cmath>
#include <cstdlib>

using namespace std;
typedef unsigned long long int ull;

int pp(int n){
	if( n == 0) return 1;
	int ret = 1;
	for(int c = 0; c < n; c++) ret *= 10;
	return ret;
}

int digits(ull n){
	if( n < 10 ) return 1;
	return 1 + digits(n/10);
}

const ull MAX = 1000000+1;
void showResult(ull *ar);


int main(int argc,char * argv[]){
	ull *numbers = new ull[MAX];
	ull cnt = 1;
	ull ind = 0;
	while(true){
		ull tmp = cnt;
		int tAr[digits(cnt)];
		for(int c = 0; c < digits(cnt);c++){
			tAr[c] = tmp % 10;
			tmp /= 10;
		}
		for(int c = 0; c < digits(cnt);c++){
			numbers[ind++] = tAr[ digits(cnt) - c - 1 ];
			if( ind == MAX - 1 ) showResult(numbers);
		}
		cnt++;
	}
}

void showResult(ull *ar){
	ull res = 1;
	for(int c = 0; c < 6; c++){
		res *= ar[pp(c+1)-1];
	}
	cout << res;
	exit(0);
}
