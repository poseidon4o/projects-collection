#include <iostream>

using namespace std;

int main(int argc,char *argv[]){
    int s1 = 0;
    int s2 = 0;
    for(int c = 1; c <= 100; c++){
        s1 += c*c;
        s2 += c;
    }
    s2 *= s2;
    int res = s2 - s1;
    cout<<res<<endl<<s1<<endl<<s2;
	return 0;
}
