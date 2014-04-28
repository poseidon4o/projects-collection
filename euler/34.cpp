#include <iostream>

typedef unsigned long long int ull;

using namespace std;

inline ull fact(int n);

int main(int argc,char *argv[]){
	int total = 0;
	int num = 10;
	ull s, n;
	ull nSum = 0;
	while(1){
		n = num;
		s = 0;
		while( n > 0 ){
			s += fact(n%10);
			n /= 10;
		}
		if( s == num ){
			nSum += s;
			total++;
			cout<<total<<" "<<s<<" "<<nSum<<endl;
		}
		if( num % 10000000 == 0 ) cout<<num<<"---"<<endl;
		num++;
	}

	return 0;
}

inline ull fact(int n){
	ull a = 1;
	for(int c = 1; c <= n; c++) a *= c;
	return a;
}
