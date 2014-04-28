#include <iostream>

using namespace std;
typedef unsigned long long int ull;

void clear(int *a,int size) {
    for(int c = 0; c < size; ++c)
		a[c] = 0;
}
bool same(int *a,int *b,int s) {
    for(int c = 0; c < s; ++c)
		if( a[c] != b[c] )
		return false;
    return true;
}

bool check(int n,int *d,int s) {
    for(int c = 2; c <= 6; ++c) {
        int nD[s];
        clear(nD,s);
        int tmp = n*c;
        while(tmp) {
            nD[tmp%10]++;
            tmp /= 10;
        }
        if( !same(d,nD,s) ) return false;
    }
    return true;
}

int main(int argc,char * argv[]) {
    int s = 10;
    int digits[s];


    int num = 1;
    while(1) {
        clear(digits,s);
        int tmp = num;
        while(tmp) {
            digits[ tmp%10 ]++;
            tmp /= 10;
        }
        if( check(num,digits,s) ) {
            cout << num;
            return 0;
        }
        ++num;
    }

    return 0;
}
