#include <iostream>

using namespace std;

bool isPanD(int a,int b,int c){
	int d[10] = {0,};
	while(a){
		if( d[a%10] != 0) return false;
		d[a%10] = 1;
		a /= 10;
	}
	while(b){
		if( d[b%10] != 0) return false;
		d[b%10] = 1;
		b /= 10;
	}
	while(a){
		if( d[c%10] != 0) return false;
		d[c%10] = 1;
		c /= 10;
	}
	return true;
}

int digits(int a,int b,int c){
	int d = 0;
	while(a){
		d++;
		a /= 10;
	}

	while(b){
		d++;
		b /= 10;
	}

	while(c){
		d++;
		c /= 10;
	}
	return d;
}

bool added(int *ar,int size,int val){
	for(int c = 0; c < size; c++)
		if(ar[c] == val) return true;
	return false;
}

void add(int val,int *ar,int size,unsigned long long *sum){
	*sum += val;
	ar[size] = val;
}

int main(int argc,char * argv[]){
	unsigned long long sum = 0;
	int cnt = 0;
	int *nums = new int[100000];

	for(int c = 1; c < 1000; c++)
		for(int r = 1; r < 1000; r++)
		if( digits(c,r,r*c) == 9 && isPanD(r,c,r*c) && !added(nums,cnt,r*c) ) add(r*c,nums,cnt++,&sum);

	for(int c = 0; c < cnt; c++) cout << nums[c] << " ";
	return 0;
}
