#include <iostream>
#include <algorithm>

using namespace std;

int main(){
	int myints[] = {1,2,3,4,5,6,7,8,9,0};

	sort(myints,myints+10);

	int cnt = 1;
	do{
		cnt ++;
		next_permutation(myints,myints+10);
	}while( cnt < 1000000 );

	for(int c = 0; c < 10; c++)
		cout << myints[c];
	return 0;
}
