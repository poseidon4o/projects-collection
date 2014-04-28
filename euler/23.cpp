#include <iostream>

using namespace std;

inline bool isAbund(int n);
inline int sumOfDev(int n);

int main(int argc,char *argv[]){

	unsigned long long int sum = 0;
	int top = 28123;



	for(int c = 1; c <= top; c++ ){
		bool add = true;
		for(int p = 11; p < c-11; p++){
			if( isAbund(p) && isAbund(c-p) ){
				add = false;
				break;
			}
		}
		if(add) {
			sum += c;
		}
	}
	cout<<sum;
	return 0;
}


inline int sumOfDev(int n){
	if( n < 12 || n > 28123 )return false;
	int sum = 0;
	for(int c = 1; c <= n/2; c++){
		if( n % c == 0) sum +=c;
	}
	return sum;
}

inline bool isAbund(int n){
	if( sumOfDev(n) > n ) return true;
	return false;
}
