#include <iostream>

using namespace std;

void multiply(int inp[]);

int main(int argc,char *argv[]){
	int res[1000] = {0};
	res[0] = 2;
	for(int c = 0; c < 999; c++){
		multiply(res);
	}
	int sum = 0;
	for(int c = 0; c < 1000; c++){
		sum += res[c];
		cout<<res[c];
	}
	cout<<endl<<sum;
	return 0;
}

void multiply(int inp[]){
	int prenos = 0;
	int cnt = 0;
	for(int c = 0; c < 1000; c++){
		int tmp = 0;
		tmp = inp[c] * 2 + prenos;
		inp[c] = tmp % 10;
		prenos = tmp / 10;
		cnt = c;
	}
	while(prenos > 0){
		cnt++;
		inp[cnt] = prenos % 10;
		prenos /= 10;
	}
}
