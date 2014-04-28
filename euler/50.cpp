#include <iostream>
#include <cmath>

using namespace std;

bool isPrime(int n){
	if( (n % 2 == 0 && n != 2) || n == 1 ) return false;
	int top = sqrt(n);
	for(int c = 3; c <= top; c+=2)
		if( n % c == 0 ) return false;
	return true;
}

const int MAX = 78498;
const int topLimit = 1000000;

int main(int argc,char * argv[]){
	int *sieve = new int[MAX];
	int num = 3;
	sieve[0] = 2;
	int cnt = 1;
	while(cnt < MAX && num < topLimit){
		if( isPrime(num) ){
			sieve[cnt++] = num;
		}
		num+=2;
	}

	int maxLen = 0;
	int maxSum = 0;
	for(int c = 0; c < MAX;++c){
		int sum = 0;
		int len = 0;
		for(int r = c; r < MAX && sum < topLimit; ++r){
			sum += sieve[r];
			len++;
			if( sum < topLimit && isPrime(sum) && len > maxLen ){
				maxSum = sum;
				maxLen = len;
			}
		}

	}
	cout << maxSum;
	return 0;
}
