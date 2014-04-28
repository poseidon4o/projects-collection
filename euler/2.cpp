#include <iostream>

using namespace std;

int main(){

    int p1 = 1;
    int p2 = 2;
    int max = 4000000;
    int fib = p1 + p2;
    long int sum = 0;
    while(1){
        if( fib > max) break;

        if(fib % 2 == 0) {
            sum += fib;
            cout<<fib<<" "<<sum<<endl;
        }
        fib = p1 + p2;

        p1 = p2;
        p2 = fib;
    }
    sum += 2;
    cout<<sum;
    return 0;
}
