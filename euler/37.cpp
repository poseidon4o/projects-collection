#include <iostream>
#include <cmath>

typedef unsigned long long int ull;

using namespace std;

bool isPrime(ull n);
int digits(ull n);
ull truncateL(ull n);
ull truncateR(ull n);
int pp(int n);

int main(int argc,char *argv[]){
	int nums = 0;
	ull sum = 0;
	ull current = 11;
	for( ; nums < 11; current+=2){
		if(!isPrime(current)) continue;
		ull L,R;
		R = L = current;
		bool cont = false;
		while( (R = truncateR(R) )&&(L = truncateL(L)) ){
			if(!isPrime(R) || !isPrime(L)){
				cont = true;
				break;
			}
		}

		if(cont) continue;

		nums++;
		sum += current;
		cout << nums << " " << current << endl;
	}
	cout << sum;
	return 0;
}

int pp(int n){
	int ret = 1;
	for(int c = 0; c < n; c++) ret *= 10;
	return ret;
}

bool isPrime(ull n){
	if( n < 2 ) return false;
	if( n % 2 == 0 ) return n == 2;
	if( n % 3 == 0 ) return n == 3;
	for(ull c = 5; c*c <= n; c+=2)
		if( n % c == 0 ) return false;
	return true;
}

ull truncateL(ull n){
	if( n < 10) return 0;
	n -= ( n / pp(digits(n)-1)) * pp(digits(n)-1);
	return n;
}

ull truncateR(ull n){
	if( n < 10 ) return 0;
	n /= 10;
	return n;
}


int digits(ull n){
	if( n < 10 ) return 1;
	if( n < 100 ) return 2;
	if( n < 1000 ) return 3;
	if( n < 10000 ) return 4;
	if( n < 100000 ) return 5;
	if( n < 1000000 ) return 6;
	if( n < 10000000 ) return 7;
	if( n < 100000000 ) return 8;
	if( n < 1000000000 ) return 9;
	if( n < 10000000000 ) return 10;
	if( n < 100000000000 ) return 11;
	if( n < 1000000000000 ) return 12;
}
