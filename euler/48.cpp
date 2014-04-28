#include <iostream>

using namespace std;

void multiply(int *num,int size,int mul){
	while(mul){
		int tmp = mul % 10;
		mul /= 10;
		for(int c = 0; c < size;++c){
			int t = (num[c]*tmp);
			if( t+num[c] > 9 ){
				int p = c;
				while( p < size && t){
					num[p] = t % 10 + num[p];
					t /= 10;
					p++;
				}
			}else{
				num[c] = t+num[c];
			}
		}
	}
}

int main(int argc,char * argv[]){
	const int size = 10;
	int num[size] = {1,}; //1234567089
	for(int c = 0; c < 10; ++c) multiply(num,size,2);
	for(int c = 0; c < size; ++c) cout << num[c];



	return 0;
}
