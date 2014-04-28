#include <iostream>

using namespace std;

int getTens(int n);
int getHundreds(int n);

int main(int argc,char *argv[]){
	int sum = 0;
	for(int c = 1; c <= 999; c++){
		sum += (getHundreds(c) + getTens(c));
	}
	sum += 11;
	cout<<sum;

	return 0;
}



int getTens(int n){
	int num = n % 100;
	int L = num % 10;
	int H = num / 10;
	int ret = 0;
	if( num == 10 ) return 3;

	if(num > 10 && num < 20){
		switch(num){
			case 11:
			case 12:
				ret += 6;
				break;
			case 13:
			case 14:
			case 19:
			case 18:
				ret += 8;
				break;
			case 17:
				ret += 9;
				break;
			case 15:
			case 16:
				ret += 7;
				break;
		}
		return ret;
	}

	switch(L){
		case 1:
		case 2:
		case 6:
			ret += 3;
			break;
		case 3:
		case 7:
		case 8:
			ret += 5;
			break;
		case 4:
		case 5:
		case 9:
			ret += 4;
			break;
		case 0:
			ret += 0;
			break;
		default:
			ret += 0;
	}

	switch(H){
		case 2:
		case 3:
		case 8:
		case 9:
			ret += 6;
			break;
		case 4:
		case 5:
		case 6:
			ret += 5;
			break;
		case 7:
			ret += 7;
			break;
		case 0:
			ret += 0;
			break;
		default:
			ret += 0;
	}
	return ret;
}

int getHundreds(int n){
	if(n < 100) return 0;
	int ret = 7; // hundred
	int num = n % 1000;
	int L = num / 100;
	if( n % 100 > 0) ret += 3;// and

	switch(L){
		case 1:
		case 2:
		case 6:
			ret += 3;
			break;
		case 3:
		case 7:
		case 8:
			ret += 5;
			break;
		case 4:
		case 5:
		case 9:
			ret += 4;
			break;
		case 0:
			ret += 0;
			break;
		default:
			ret += 0;
	}

	return ret;
}
