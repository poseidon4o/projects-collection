#include <iostream>

using namespace std;

inline unsigned long int getNext(unsigned long int n);

int main(int argc,char *argv[]){
	int max = 1000000;
	int top = -1;

	for(int c = 1; c < max; c++){
		unsigned long int ret = c;
		int cnt = 0;
		do{
			cnt++;
			ret = getNext(ret);
		}while(ret > 1);
		if(cnt > top) {
			top = cnt;
			cout<<top<<" "<<c<<endl;
		}
	}


	/*for(;max > 0; max--){
		int ret = max;
		int cnt = 0;
		do{
			ret = getNext(ret);
			cnt++;
		}while(ret > 1);
		if( cnt > 400 ){
			cout<<max<<" - "<<cnt<<endl;
		}
		if( cnt > top ) {
			num = max;
			top = cnt;
		}
	}*/
	//cout<<top<<" "<<num<<endl<<max;


	return 0;
}

inline unsigned long int getNext(unsigned long int n){
	if( n % 2 == 0 ) return n/2;
	return (3*n + 1);
}
