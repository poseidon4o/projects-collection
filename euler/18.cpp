#include <iostream>

using namespace std;

void str2tri(int a[],int ret[][15]);
inline void calcCell(int row,int col,int a[][15]);
inline int max(int a, int b);
//inline void getNext(int row,int col, int a[][15],int sum[],int index);
//inline int getFreeIndex(int sum[]);

int main(int argc,char *argv[]){
	int a[] = {75,95,64,17,47,82,18,35,87,10,20,4,82,47,65,19,1,23,75,3,34,88,2,77,73,7,63,67,99,65,4,28,6,16,70,92,41,41,26,56,83,40,80,70,33,41,48,72,33,47,32,37,16,94,29,53,71,44,65,25,43,91,52,97,51,14,70,11,33,28,77,73,17,78,39,68,17,57,91,71,52,38,17,14,91,43,58,50,27,29,48,63,66,4,68,89,53,67,30,73,16,69,87,40,31,4,62,98,27,23,9,70,98,73,93,38,53,60,4,23};
	int triangle[15][15] = { {0} };
	str2tri(a,triangle);

	for(int r = 0; r < 15; r++){
		for(int c = 0; c < 15; c++){
			if(triangle[r][c ] < 10) cout<<0;
			cout<<triangle[r][c]<<"|";
		}
		cout<<endl;
	}

	for(int row = 1; row < 15; row++){
		for(int col = 0; col <= 14 - row; col++){
			cout<<row<<" "<<col<<endl;
			calcCell(row,col,triangle);
		}
	}
	cout<<endl<<"----------------------------------------"<<endl;
	for(int r = 0; r < 15; r++){
		for(int c = 0; c < 15; c++){
			if(triangle[r][c ] < 10) cout<<0;
			cout<<triangle[r][c]<<"|";
		}
		cout<<endl;
	}
/*
	int sums[20000] = {0};
	for(int c = 0; c < 15; c++){
		int tIndex = getFreeIndex(sums);
		sums[tIndex] = triangle[0][c];
		getNext(0,c,triangle,sums,tIndex);
	}

	for(int c = 0; c < 20000; c++){
		for(int r = 0; r < 19999; r++){
			if(sums[r] < sums[r+1]){
				int tmp = 0;
				tmp = sums[r];
				sums[r] = sums[r+1];
				sums[r+1] = tmp;
			}
		}
	}
	cout<<sums[0]<<" "<<sums[1];
*/


	return 0;
}

inline void calcCell(int row,int col,int a[][15]){
	a[row][col] += max(a[row-1][col],a[row-1][col+1]);
}

inline int max(int a, int b){
	if(a > b) return a;
	return b;
}
/*
inline void getNext(int row,int col, int a[][15],int sum[],int index){
	if(row == 14){
		sum[index] += a[14][0];
		return;
	}
	sum[index] += a[row][col];
	if(col == 15 - row - 1){
		getNext(row+1,col-1,a,sum,index);
		return;
	}else if(col == 0){
		getNext(row+1,col,a,sum,index);
		return;
	}else{
		getNext(row+1,col,a,sum,index);
		int nInd = getFreeIndex(sum);
		sum[nInd] = sum[index];
		getNext(row+1,col-1,a,sum,nInd);
		return;
	}
}

inline int getFreeIndex(int arr[]){
	for(int c = 0; c < 20000; c++){
		if(arr[c] == 0) return c;
	}
}
*/
void str2tri(int a[], int ret[][15]){
	for(int row = 0; row < 15; row ++){

		for(int num = 0; num <= row; num++){
			int k = row*(row + 1)/2 + num ;
			ret[14-row][num] = a[k];
		}

	}
}
