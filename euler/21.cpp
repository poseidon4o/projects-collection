#include <iostream>

using namespace std;

int sumOfDev(int n);

int main(int argc,char *argv[]){
	unsigned long long int sum = 0;
	for(int c = 1; c < 10000; c++){
		int tS = sumOfDev(c);
		if( sumOfDev(tS) == c && tS != c ) sum += c;
	}
	cout<<sum;
	return 0;
}

int sumOfDev(int n){
	int sum = 0;
	for(int c = 1; c <= n/2; c++){
		if( n % c == 0 ) sum += c;
	}
	return sum;
}
