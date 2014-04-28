#include <iostream>
#include <cmath>

using namespace std;

const int MAX = 10000;
const int memSize = 100;
int memo[memSize][2];
int memCnt = 0;

bool inMem(int n,int *p){
	for(int c = 0; c < memSize; c++){
		if( memo[c][0] == -1 ) return false;
		if( memo[c][0] == n ){
			*p = memo[c][1];
			return true;
		}
	}
	return false;
}

bool isPrime(int n){
	if( (n % 2 == 0 && n != 2) || n == 1 ) return false;
	int top = sqrt(n);
	for(int c = 3; c <= top; c+=2)
		if( n % c == 0 ) return false;
	return true;
}

int sums(int n,int *ar,int size,int start){
	int s = 0,c = start;
	bool add = false;
	if( inMem(n,&s) ) return s;
	else add = true;
	while( ar[c] <= n && c < size ){
		if( n - ar[c] == 0 ){
			++s;
		}else if( n - ar[c] > 0){
			s += sums( n - ar[c],ar,size,c);
		}else{
			break;
		}
		c++;
	}

	if(add){
		memo[memCnt][0] = n;
		memo[memCnt][1] = s;
		++memCnt;
	}
	return s;
}

int main(int argc,char * argv[]){
	for(int c = 0; c < memSize; c++) memo[c][0] = memo[c][1] = -1;
	int *sieve = new int[MAX];
	sieve[0] = 2;
	for(int c = 1, p = 3; c < MAX; p+=2)
		if( isPrime(p) ) sieve[c++] = p;

	int r = 0,q = 1;
	while( r < 50000 ){

		r = sums(q,sieve,MAX,0)-1;
		cout << q << " " << r << endl;
		q++;
	}

	for(int c = 0; c < memSize; c++)
		cout << memo[c][0] << " - " << memo[c][1] << endl;

	return 0;
}
