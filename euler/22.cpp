#include <iostream>
#include <stdio.h>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

#include "names.cpp"

int wordVal(std::string word);

int main(int argc,char *argv[]){
	int count = sizeof(names)/sizeof(string);

	vector<string> namesVec (names, names + count);

	sort(namesVec.begin(),namesVec.end());

	int total = 0;
	for(int c = 0; c < namesVec.size(); c++){
		total += (c+1)*wordVal(namesVec[c]);
	}
	cout << total;

	return 0;

}

int wordVal(std::string word){
	int sum = 0;
	for(int c = 0; c < word.length(); c++)
		sum += (int)(word[c] - 64);
	return sum;
}
