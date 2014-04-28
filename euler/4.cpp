#include <iostream>

using namespace std;

inline bool isPalindrome(int n);
inline bool isProduct(int n);
int main(int argc,char *argv[]){

    int max = 999*999;
    int min = 100*100;
    for(; max > min; max--){
        if(isPalindrome(max) and isProduct(max)){
            cout<<max;
            return 0;
        }
    }

	return 0;
}

inline bool isProduct(int n){
    for(int c = 999; c >= 100; c--){
        for(int p = 999; p >= 100; p--){
            if(p*c == n) return true;
        }
    }
    return false;
}



inline bool isPalindrome(int n){
    int t = n;
    int len = 0;
    while( t > 0){
        t /= 10;
        len++;
    }
    int nums[len];
    t = n;
    int c = 0;
    while( t > 0){
        nums[c] = t % 10;
        t /= 10;
        c++;
    }
    for(int c = 0; c <= len/2; c++){
        if(nums[c] != nums[len-c-1]) return false;
    }
    return true;
}
