#include <iostream>

using namespace std;

inline int devisorsOf(int n);

int main(int argc,char *argv[]){
	int num = 0;
	for(;; num++){
		int dev = devisorsOf(num*(num-1)/2);
		if( dev > 500 ){
			cout<<(num*(num-1)/2);
			break;
		}
	}
	return 0;
}

inline int devisorsOf(int n){
	int cnt = 1;
	for(int c = 1; c <= n/2; c++){
		if( n % c == 0) cnt++;
	}
	return cnt;
}
