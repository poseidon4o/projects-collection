#include <iostream>
#include <cmath>
using namespace std;

bool inline isPrime(int n);

int main(int argc,char *argv[]){
	unsigned long long int sum = 2;
	int n = 3;
	while( n < 2000000 ){
		if(isPrime(n)) sum += n;
		n++;
	}
	cout<<sum;
	return 0;
}

inline bool isPrime(int n){
    for(int c = 2; c <= sqrt(n); c++){
        if( n % c == 0) return false;
    }
    return true;
}
