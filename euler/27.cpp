#include <iostream>
#include <cmath>

using namespace std;

inline bool isPrime(int n);
inline bool inPrime(int n,int *arr);

int main(int argc,char *argv[]){
	int *primes;
	primes = new int[10000];
	int counter = 0, c = 2;
	do{
		if(isPrime(c)){
			primes[counter] = c;
			counter++;
		}
		c++;
	}while(counter < 10000);


	int sequence = 0, save = 0;
	for(int a = -999; a < 999; a++){
		cout<<"a:"<<a<<endl;
		for(int b = -999; b < 999; b++){
			int res = 0, x = 0;
			do{
				res = x*x + a*x + b;
				x++;
			}while(inPrime(res,primes));
			if( x > sequence ){
				sequence = x;
				save = a*b;
			}
		}
	}
	cout<<save;
	return 0;
}

inline bool inPrime(int n,int *arr){
	for(int c = 0; c < 1000; c++) if(arr[c] == n) return true;
	return false;
}

inline bool isPrime(int n){
	int max = sqrt(n);
	if( ! n % 2 ) return false;
	for(int c = 3; c <= max; c+=2) 
		if(n % c == 0) 
			return false;
	return true;
}
