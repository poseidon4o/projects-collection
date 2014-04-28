#include <iostream>
#include <cmath>

typedef unsigned long long int ull;

using namespace std;

inline bool isViable(int n);

int main(int argc,char *argv[]){
	ull sum = 0;
	int tmp = 0;
	for(int c = 10; c < 1000000; c++){
		if(isViable(c)) sum += c;
	}
	cout<<sum;
	return 0;
}

inline bool isViable(int n){
	int tmp = 0, r = n;
	while(n > 0){
		tmp += pow(n%10,5);
		n /= 10;
	}
	if( r == tmp ) return true;
	return false;
}
