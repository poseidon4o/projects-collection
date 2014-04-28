#include<iostream>
using namespace std;

int main(){
    int bar[1001]={0};
    bar[1000]=1;
    int p = 0;
    int k = 0;
    int c = 0;
    int m = 0;
    for(int i = 2;i<=5;i++){
        for(int j=1000;j>=0;j--){
            c =bar[j]*i;
            bar[j]=c%10;
            if(p!=0){
                bar[j]=bar[j]+p;
                if(bar[j]>=10){
                    m=bar[j]/10;
                    bar[j]=bar[j]%10;
                }
                p=0;
            }
            if(c>=10){
                p= c/10;
                if(k!=0){
                    p = p + k;
                    k=0;
                }
                if(m!=0){
                    p=p+m;
                    m=0;
                }
                if(p>=10){
                    k=p/10;
                    p=p%10;
                }
            }
        }
    }
    for(int h = 1;h<1001;h++){
            cout<<bar[h]<<" ";
    }
    cout<<endl;
    int count = 0;
    for(int h = 1000;h>=0;h--){
        count = count + bar[h];
    }
    cout<<count;
    return 0;
}
