#include <iostream>
#include <cmath>

using namespace std;

typedef unsigned long long int ull;

const int size = 25; // primes below 100

bool isPrime(int n){
	if( (n % 2 == 0 && n != 2) || n == 1 ) return false;
	int top = sqrt(n);
	for(int c = 3; c <= top; c+=2)
		if( n % c == 0 ) return false;
	return true;
}

void cpy(int a[size][2],int b[size][2]){
	for(int c = 0; c < size;++c){
		b[c][0] = a[c][0];
		b[c][1] = a[c][1];
	}
}

void addDev(int n,int loc[size][2]){
	while( n != 1 ){
		for(int c = 0; c < size; c++){
			if( n % loc[c][0] == 0 ){
				n /= loc[c][0];
				loc[c][1]++;
			}
		}
	}
}

ull comb(int n,int r,int sieve[size][2]){
	int top[size][2];
	int bottom[size][2];
	cpy(sieve,top);
	cpy(sieve,bottom);

	for(int c = 1; c <= n; ++c){
		addDev(c,top);
	}
	for(int c = 1; c <= r; ++c){
		addDev(c,bottom);
	}
	for(int c = 1; c <= n-r; ++c){
		addDev(c,bottom);
	}

	for(int c = 0; c < size; ++c){
		if( top[c][1] > 0 && bottom[c][1] > 0 ){
			if( top[c][1] > bottom[c][1] ){
				top[c][1] = top[c][1] - bottom[c][1];
				bottom[c][1] = 0;
			}else if( top[c][1] < bottom[c][1] ){
				bottom[c][1] = bottom[c][1] - top[c][1];
				top[c][1] = 0;
			}else{
				top[c][1] = bottom[c][1] = 0;
			}

		}
	}

	ull t = 1,b = 1;
	for(int c = 0; c < size; ++c){
		while( top[c][1] ){
			t *= top[c][0];
			top[c][1]--;
		}
		while( bottom[c][1] ){
			b *= bottom[c][0];
			bottom[c][1]--;
		}
	}
	return t/b;

}



int main(int argc,char * argv[]){
	int sieve[size][2];
	int cnt = 0;
	for(int c = 1; c < 101;++c){
		if( isPrime(c) ){
			sieve[cnt][0] = c;
			sieve[cnt++][1] = 0;
		}
	}
	int tot = 0;
	for(int c = 1; c <= 100; c++)
		for(int r = 1; r <= c; r++)
			if( comb(c,r,sieve) > 1000000 ) ++tot;

	cout << tot;



	return 0;
}
