#include <iostream>

using namespace std;

int main(int argc,char *argv[]){
    int min = 2520;
    bool good = true;
    while(1){
        good = true;
        for(int c = 1; c <= 20; c++){
            if( min % c != 0){
                good = false;
                break;
            }
        }
        if(!good) min+=3;
        else{
            cout<<min;
            return 0;
        }
    }
	return 0;
}
