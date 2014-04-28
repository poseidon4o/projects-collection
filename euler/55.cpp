#include <iostream>

using namespace std;
typedef unsigned long long int ull;


ull digits(ull n){
	return n ? 1 + digits(n/10) : 0;
}

ull pp(ull a,ull b){
	return b ? a * pp(a,b-1) : 1;
}

ull next(ull n){
	ull d = digits(n);
	ull p = n;
	for(ull c = 0; c < d; ++c){
		p += (n%10) * pp(10,d-c-1);
		n /= 10;
	}
	return p;
}

bool isPalindrome(ull n){
    ull t = n;
    ull len = 0;
    while( t > 0){
        t /= 10;
        len++;
    }
    ull nums[len];
    t = n;
    ull c = 0;
    while( t > 0){
        nums[c] = t % 10;
        t /= 10;
        c++;
    }
    for(ull c = 0; c <= len/2; c++){
        if(nums[c] != nums[len-c-1]) return false;
    }
    return true;
}

int main(int argc,char * argv[]){

	ull lych = 0;
	for(ull c = 10; c <= 10000; ++c){
		ull tmp = c;
		if( isPalindrome(tmp) ) continue;
		bool add = true;
		for(ull it = 0; it < 50; it++){
			tmp = next(tmp);
			if( isPalindrome(tmp) ){
				add = false;
				break;
			}
		}
		if(add){
			cout << tmp << endl;
			lych++;
		}

	}
	cout << lych;
	return 0;
}
