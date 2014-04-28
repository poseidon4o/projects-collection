#include <iostream>

using namespace std;

int main(int argc,char *argv[]){
	unsigned long long int grid[21][21] = { {0} };
	for(int c = 0; c < 21; c++){
		grid[c][0] = 1;
		grid[0][c] = 1;
	}
	for(int r = 1; r < 21; r++){
		for(int c = 1; c < 21; c++){
			grid[r][c] = grid[r-1][c] + grid[r][c-1];
		}
	}
	cout << grid[20][20];
	return 0;
}
