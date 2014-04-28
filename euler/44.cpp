#include <iostream>

using namespace std;
typedef unsigned long long int ull;

bool inArray(int key,int *ar, int last) {
    int first = 0;
    int mid;
    while (first <= last) {
        mid = (first + last) / 2;
        if (key > ar[mid])
            first = mid + 1;
        else if (key < ar[mid])
            last = mid - 1;
        else
            return true;
    }
    return false;
}

inline int abs(int n) {
    return n < 0 ? -n : n;
}

int main(int argc,char * argv[]) {
    const int MAX = 10000;
    int *ar = new int[MAX];
    for(int c = 1; c < MAX; c++)
        ar[c] = c*(3*c-1)/2;

    for(int c = 1; c < MAX; ++c) {
        for(int r = c; r < MAX; ++r) {
            int p = c*(3*c-1)/2;
            int q = r*(3*r-1)/2;
            if( inArray(p+q,ar,MAX) && inArray(abs(p-q),ar,MAX) ) {
                cout << p << " " << q << " " << abs(p-q);
                return 0;
            }
        }
    }
    return 0;
}
