#include <iostream>
#include <cmath>

using namespace std;

int digits(int n){
    if( n >= 100000 && n < 1000000 ) return 6;
    if( n >= 10000 && n < 100000 ) return 5;
    if( n >= 1000 && n < 10000 ) return 4;
    if( n >= 100 && n < 1000 ) return 3;
    if( n >= 10 && n < 100 ) return 2;
    if( n >= 0 && n < 10 ) return 1;
	return 6;
}

int pp(int n){
	int ret = 1;
	for(int c = 0; c < n; c++) ret *= 10;
	return ret;
}

int cycle(int n){
	if( n < 10) return n;
	return (n % 10)*pp(digits(n)-1) + (n/10) ;
}

bool isPrime(int n){
	if( (n % 2 == 0 && n != 2) || n == 1 ) return false;
	int top = sqrt(n);
	for(int c = 3; c <= top; c+=2)
		if( n % c == 0 ) return false;
	return true;
}

int main(int argc,char * argv[]){

	int cnt = 0;
	for(unsigned long c = 1; c < 1000000; c++){

		int dd = digits(c);
		int tmp = c;
		bool add = true;
		for(int k = 0; k < digits(tmp)+1; k++){
			if(!isPrime(tmp)){
				add = false;
				break;
			}
			tmp = cycle(tmp);
		}
		if(add)	cnt++;
	}
	cout << cnt;

	return 0;
}
