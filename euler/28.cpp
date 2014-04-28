#include <iostream>

using namespace std;

int main(int argc,char *argv[]){
    //500/500, 501/500, 501/501, 500/501, 499/501, 499/500, 499/499,
    int mVec[501] = {0};
    int sVec[501] = {0};
    int tVec[501] = {0};
    int fVec[501] = {0};
    mVec[0] = 1;
    int step = 0;
    for(int circle = 0; circle < 501; circle++){
		mVec[circle] = (step+1)*(step+1);
		sVec[circle] = mVec[circle] - step;
		tVec[circle] = sVec[circle] - step;
		fVec[circle] = tVec[circle] - step;
		step+=2;
    }
    unsigned long long int sum = 0;
    for(int c = 1; c < 501; c++){
    	sum  += mVec[c] + sVec[c] + tVec[c] + fVec[c];
    }
    sum++;
    cout<<sum;
	return 0;
}
