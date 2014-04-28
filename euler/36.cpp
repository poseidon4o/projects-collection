#include <iostream>

using namespace std;

bool isPdec(int a){
	int num[10] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
	int cnt = 0;
	while(a){
		num[cnt++] = a % 10;
		a /= 10;
	}
	for(int c = 0; c < cnt/2;++c){
		if( num[c] != num[cnt-c-1] ) return false;
	}
	return true;
}

bool isPbin(int a){
	int size = 50;
	int *ret = new int[size];
	for(int c = 0; c < size; ++c)
		ret[c] = -1;
	int cnt = 0;
	while(a){
		ret[cnt++] = a % 2;
		a /= 2;
	}
	for(int c = 0; c < cnt; ++c)
		if( ret[c] != ret[cnt-c-1] ) return false;

	return true;
}



int main(int argc,char * argv[]){
	long long sum = 0;
	for(int c = 0; c < 1000000; ++c)
		if( isPbin(c) && isPdec(c) ) sum+=c;
	cout << sum;
	return 0;
}
