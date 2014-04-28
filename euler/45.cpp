#include <iostream>
#include <limits>

using namespace std;

typedef unsigned long long int ull;

const ull MAX = numeric_limits<ull>::max( );

int main(int argc,char * argv[]) {

    ull num;
    ull cnt = 1;
    while( (cnt*(cnt+1))/2 <= 40755) ++cnt;
    ull lastP = 1,lastH = 1;
    for( ; cnt < MAX; ++cnt) {
        bool con = false;
        ull tr = (cnt*(cnt+1))/2;
        if( tr > MAX ) {
            break;
        }
        for( ull p = lastP;  ; ++p) {
            ull pe = (p*(3*p-1))/2;
            if( pe > MAX  || pe > tr) {
                con = true;
                break;
            }
            if( pe == tr ) break;
            if( pe < tr ) lastP = p;
        }
        if( con ) continue;
        for( ull h = lastH; ; ++h) {
            ull he = h*(2*h-1);
            if( he > MAX || he > tr) {
                con = true;
                break;
            }
            if( he == tr ) break;
            if( he < tr ) lastH = h;
        }
        if( con ) continue;
        cout << cnt << " " << tr << endl;
        return 0;
    }

    return 0;
}
