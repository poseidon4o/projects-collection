#include <iostream>
#include <cmath>

using namespace std;

typedef unsigned ul;

bool isPrime(ul n){
	if( (n % 2 == 0 && n != 2) || n == 1 ) return false;
	if( n == 2 ) return true;
	int top = sqrt(n) + 1;
	for(int c = 3; c <= top; c+=2)
		if( n % c == 0 ) return false;
	return true;
}

bool is_pandigital(ul n){
	bool digits[9];
	for(int c = 0; c < 10; ++c)
        digits[c] = 0;

    int tot_digits = 0;
    while( n ) {
        tot_digits++;
        digits[n % 10-1]++;
        n /= 10;
    }

    for(int c = 0; c < tot_digits; ++c) {
        if ( digits[c] != 1 )
            return false;
    }
    return true;
}


int main(int argc,char * argv[]){

    ul n = 3;
    ul top = (ul)pow(10,9);
    while( n += 2 < top ) {
        if( is_pandigital(n) && isPrime(n) ) {
            cout << n << endl;
        }
    }


	return 0;
}


/*
int *perm(int len,int *size){
	if( len > 1){
		int n = 0;
		int *ret = perm(len-1,&n);
		int *nArray = new int[10*n];
		int ind = 0;
		for(int c = 0; c < n; c++){
			for(int p = 0; p < 10; p++){
				nArray[ind++] = ret[c] * 10 + p;
			}
		}
		*size = 10*n;
		return nArray;
	}else{
		int *ar = new int[10];
		for(int c = 0; c < 10; c++) ar[c] = c;
		*size = 10;
		return ar;
	}
}
*/
