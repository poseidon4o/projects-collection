#include <iostream>
#include <ttmath/ttmath.h>

using namespace std;

int main(int argc,char *argv[]){
	ttmath::UInt<100> sum;
	ttmath::UInt<100> *numbers = new ttmath::UInt<100>[250000];
	int index = 0;

	for(int a = 2; a <= 100; ++a){
		for(int b = 2; b <= 100; ++b){
			sum = "1";
			for(int c = 0; c < b;c++){
				sum *= a;
			}
			bool add = true;
			for(int c = 0; c < index; ++c){
				if( numbers[c] == sum ){
					add = false;
					break;
				}
			}
			if(add){
				numbers[index++] = sum;
			}
		}
		cout << a << endl;
	}
	cout << index;

	return 0;
}
