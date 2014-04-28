#include <iostream>

using namespace std;

int main(int argc,char *argv[]){
    unsigned long long int n = 600851475143;
    bool prime = true;
    for(unsigned long long int c = 2; c <= n/2;c++){
        if( n % c == 0 ){
            for(unsigned long long int p = 2; p <= c/2; p++){
                if( c % p == 0){
                    prime = false;
                    break;
                }
            }
            if(prime) cout<<c<<endl;
            prime = true;
        }
    }
	return 0;
}
