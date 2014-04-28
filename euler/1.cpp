#include <iostream>

using namespace std;

int main(int argc,char *argv[]){
    long int sum = 0;
    for(int c = 1; c < 1000; c++){
        if( c % 3 == 0 || c % 5 == 0){
            sum += c;
        }
    }
    cout<<sum;
	return 0;
}
