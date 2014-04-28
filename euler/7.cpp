#include <iostream>
#include <cmath>
using namespace std;

bool inline isPrime(int n);

int main(int argc,char *argv[]){
    int target = 10001;
    int current = 1;
    int num = 3;
    while(1){
        if(isPrime(num)){
            current++;
        }
        if(current == target){
            cout<<num;
            return 0;
        }
        num++;
    }
	return 0;
}

inline bool isPrime(int n){
    for(int c = 2; c <= n/2; c++){
        if( n % c == 0) return false;
    }
    return true;
}
