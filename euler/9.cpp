#include <iostream>

using namespace std;

inline bool isTriplet(int a,int b,int c);

int main(int argc,char *argv[]){
	for(int c = 1; c < 1000; c++){
		for(int a = 1; a < 1000; a++){
			if(isTriplet(c,a,1000-a-c)){
				cout<<a<<" "<<(1000-a-c)<<" "<<c<<" = "<<(a*(1000-a-c)*c)<<endl;
				return 0;
			}
		}
	}
	return 0;
}


inline bool isTriplet(int a,int b,int c){
	if( a*a + b*b == c*c ||
		b*b + c*c == a*a ||
		c*c + a*a == b*b) return true;
	return false;
}
