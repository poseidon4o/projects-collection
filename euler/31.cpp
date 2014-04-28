#include <iostream>

using namespace std;

int main(int argc,char *argv[]){

	int total = 0;


	for(int x = 0; x <= 200; x++){
		for(int y = 0; y <= 100; y++){
			for(int z = 0; z <= 40; z++){
				for(int p = 0; p <= 20; p++){
					for(int q = 0; q <= 10; q++){
						for(int m = 0; m <= 4; m++){
							for(int n = 0; n <= 2; n++){
								if( (x + 2*y + 5*z + 10*p + 20*q + 50*m + 100*n) == 200 ) total++;
							}
						}
					}
				}
			}
		}
	}
	total++;
	cout<<total;



	return 0;
}
