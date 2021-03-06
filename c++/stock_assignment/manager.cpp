#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

using namespace std;

char FILE_INVESTORS[100] = "investors.dat";
char FILE_COMPANIES[100] = "company.dat";
char FILE_STOCKS[100]    = "stocks.dat";
const int STR_LEN = 30;
bool FLAG_ERROR = false;

const bool CACHE_ENABLE = true;

struct Investor {
	unsigned id;
	char name[STR_LEN];
	double capital;
};

struct Company{
	int id;
	char name[STR_LEN];
	double price;
};

struct Stock{
	int investorID;
	int companyID;
	double shares;
};

struct {
	int totalCompanies;
	int totalInvestors;
	int totalStocks;
	int *companies;
	int *investors;
	int *stockInvestor;
	int *stockCompany;
	int *freeSpots;
	int spotCnt;
	int spotArraySize;
} cache;

struct {
	Stock *record;
	int total;
} newStocks;


void cacheIfPossible();
bool fileExists(const char *fname);
double getCompanySoldShares(unsigned companyID);
Company getCompany(unsigned id);
Investor getInvestor(unsigned id);
Stock getStock(unsigned iID,unsigned cID);

bool buyStocks(int iID,int cID,double sum);
bool sellStocks(int iID,int cID,double sum);
bool printInvestor(int iID);

void updateStock(Stock save);
bool updateInvestor(Investor inv);
void beforeQuit();

void generateInvestors(int cnt){
	fstream file(FILE_INVESTORS,ios::out | ios::in | ios::binary | ios::trunc);
	Investor inv;
	for (int c = 0; c < cnt; ++c) {
		inv.id = c;
		inv.name[0] = 0;
		for(int n = 0; n < rand()% 30; n++){
			inv.name[n] = rand() % 26 + 65;
			if( n % 5 == 0 and n !=0 ) inv.name[n] = 32;
		}
		inv.capital = rand();
		if( !file.write( (char*)&inv, sizeof(inv) ) ){
			cout << "ERROR at " << c << endl;
			break;
		}
	}
}
void generateComapnies(int cnt){
	fstream file(FILE_COMPANIES,ios::out | ios::in | ios::binary | ios::trunc);
	Company cmp;
	for (int c = 0; c < cnt; ++c) {
		cmp.id = c;
		cmp.name[0] = 0;
		for(int n = 0; n < rand()% 30; n++){
			cmp.name[n] = rand() % 26 + 65;
			if( n % 5 == 0 and n !=0 ) cmp.name[n] = 32;
		}
		cmp.price = rand();
		if( !file.write( (char*)&cmp, sizeof(cmp) ) ){
			cout << "ERROR at " << c << endl;
			break;
		}
	}
}

int main(int argc,const char *argv[]){

	//if( argc != 4 ) {
		//cout << "ERROR";
		//return 0;
	//}

	//strcpy(FILE_INVESTORS,argv[1]);
	//strcpy(FILE_COMPANIES,argv[2]);
	//strcpy(FILE_STOCKS,argv[3]);

	if( !fileExists(FILE_INVESTORS) or !fileExists(FILE_COMPANIES) or !fileExists(FILE_STOCKS)){
		cout << "ERROR";
		return 0;
	}


	if(CACHE_ENABLE) cacheIfPossible();
    cout << "cached\n";
	char commands[10] = "bsp";

	char cmd;
	int iID, cID;
	double sum;
	while( cin >> cmd ){
		FLAG_ERROR = false;
		bool validCMD = false;
		for(char *cp = commands; *cp; cp++ ){
			if( *cp == cmd ){
				validCMD = true;
				break;
			}
		}
		if(!validCMD) break;
		if( cmd == 'b' ) {
			cin >> iID >> cID >> sum;
			if( ! buyStocks(iID,cID,sum) ) {
				cout << "ERROR";
			} else {
				cout << "OK";
			}
		} else if( cmd == 's') {
			cin >> iID >> cID >> sum;
			if( ! sellStocks(iID,cID,sum) ) {
				cout << "ERROR";
			} else {
				cout << "OK";
			}
		} else if( cmd == 'p' ) {
			cin >> iID;
			printInvestor(iID);
		}

		cout << endl;
	}


	if(CACHE_ENABLE) beforeQuit();
	return 0;
}

bool updateInvestor(Investor inv) {
	fstream file(FILE_INVESTORS,ios::in | ios::out | ios::binary | ios::ate);

	if( !file ){;
		return false;
	}

	file.seekp(0,file.beg);
	file.seekg(0,file.beg);


	if( cache.investors ) {

		int index = -1;
		for (int c = 0; c < cache.totalInvestors; ++c) {
			if( cache.investors[c] == inv.id ) {
				index = c;
				break;
			}
		}
		if( index == -1 ) {
			if( file.is_open() ) file.close();
			return false;
		}
		file.seekp( index*sizeof(inv), file.beg );
		if ( ! file.write( (char*)&inv, sizeof(inv) ) ) {
			if( file.is_open() ) file.close();
			return false;
		}
		if( file.is_open() ) file.close();
		return true;
	}
	Investor search;
	int index = 0;
	while( file.read( (char*)&search, sizeof(search) ) ) {

		if( search.id == inv.id ) {
			file.seekp( index*sizeof(inv), ios::beg  );

			if( !file.write( (char*)&inv, sizeof(inv) ) ) {
				if( file.is_open() ) file.close();
				return false;
			}
			if( file.is_open() ) file.close();
			return true;
		}
		index++;
	}
	FLAG_ERROR = true;
	if( file.is_open() ) file.close();
	return false;
}

void updateStock(Stock save){

	fstream file(FILE_STOCKS,ios::in | ios::out | ios::binary | ios::ate);

	if( !file ) {
		FLAG_ERROR = true;
		return;
	}

	file.seekg(0,file.beg);
	file.seekp(0,file.beg);

	if( save.shares <= 0 ) { // delete record
		if( cache.stockInvestor and cache.stockCompany and cache.freeSpots and newStocks.record) {

			for (int c = 0; c < cache.totalStocks; ++c) {
				if( cache.stockInvestor[c] == save.investorID and cache.stockCompany[c] == save.companyID ){

					file.seekp( c*sizeof(save), file.beg );
					save.shares = -1;
					if( !file.write( (char*)&save, sizeof(save) ) ){
						FLAG_ERROR = true;
						if( file.is_open() ) file.close();
						return;
					}

					bool append = true;
					// check freeSpots array for any spot that is taken
					for (int p = 0; p < cache.spotCnt; ++p) {
						if( cache.freeSpots[p] == -1 ) {
							cache.freeSpots[p] = c;
							append = false;
							break;
						}
					}
					if( !append ) { // we inserted into not free spot - no need to append
						if( file.is_open() ) file.close();
						return;
					}


					// need bigger array
					if( cache.spotCnt == cache.spotArraySize - 1 ) {
						cache.spotArraySize *= 2;
						int *newSpotArray = new(nothrow) int[cache.spotArraySize];
						if( !newSpotArray ){
							beforeQuit();
							if( file.is_open() ) file.close();
							return;
						}
						for (int p = 0; p < cache.spotCnt; ++p) {
							newSpotArray[p] = cache.freeSpots[p];
						}
						delete[] cache.freeSpots;
						cache.freeSpots = newSpotArray;
					}

					cache.freeSpots[cache.spotCnt++] = c;
					if( file.is_open() ) file.close();
					return;

				}
			}
			if( file.is_open() ) file.close();
			// stock not in cache - remove from newstock
			for (int c = 0; c < newStocks.total; ++c) {
				if( newStocks.record[c].companyID == save.companyID and newStocks.record[c].investorID == save.investorID ) {
					newStocks.record[c].shares = -1;
				}
			}
		} else {
			// no cache
			ofstream newFile("stock_temp",ios::out | ios::binary | ios::trunc);
			Stock mv;
			while( file.read( (char*)&mv, sizeof(mv) ) ) {
				if( mv.investorID == save.investorID and mv.companyID == save.companyID )
					continue; // skip the record
				if( !newFile.write( (char*)&mv, sizeof(mv)) ) {
					if( newFile.is_open() ) newFile.close();
					if( file.is_open() ) file.close();
					FLAG_ERROR = true;
					return;
				}
			}

			if( file.is_open() ) file.close();
			if( newFile.is_open() ) newFile.close();
			remove( FILE_STOCKS );
			rename( "stock_temp", FILE_STOCKS );
			return;
		}
	}

	if( cache.stockInvestor and cache.stockCompany and cache.freeSpots and newStocks.record) {
		int index = -1;
		for (int c = 0; c < cache.totalStocks; ++c) {
			if( cache.stockInvestor[c] == save.investorID and cache.stockCompany[c] == save.companyID ) {
				// check if stock is marked as free and mark it as taken
				for (int p = 0; p < cache.spotCnt; ++p) {
					if( cache.freeSpots[p] == c ){
						cache.freeSpots[p] = -1;
						break;
					}
				}
				index = c;
				break;
			}
		}
		if( index == -1 ){
			// stock is not cached - find free spot
			for (int c = 0; c < cache.spotCnt; ++c) {
				if( cache.freeSpots[c] != -1 ){
					index = cache.freeSpots[c];
					cache.freeSpots[c] = -1;
					break;
				}
			}
			if( index != -1 ){
				cache.stockInvestor[index] = save.investorID;
				cache.stockCompany[index] = save.companyID;
				file.seekp(index * sizeof(save),file.beg);
			} else {
				// no free spots - append to newStocks
				if( file.is_open() ) file.close();
				for (int c = 0; c < newStocks.total; ++c) {
					if (newStocks.record[c].companyID == save.companyID and newStocks.record[c].investorID == save.investorID) {
						newStocks.record[c].shares = save.shares;
						return;
					}
				}
				for (int c = 0; c < newStocks.total; ++c) {
					if( newStocks.record[c].shares ==  -1 ) {
						newStocks.record[c].companyID = save.companyID;
						newStocks.record[c].investorID = save.investorID;
						newStocks.record[c].shares = save.shares;
						return;
					}
				}
				newStocks.total *= 2;
				Stock *newAr = new(nothrow) Stock[newStocks.total];
				if( !newAr ){
					beforeQuit();
					return;
				}
				for (int c = 0; c < newStocks.total/2; ++c) {
					newAr[c] = newStocks.record[c];
				}
				delete[] newStocks.record;
				newStocks.record = newAr;
				for (int c = 0; c < newStocks.total; ++c) {
					if( newStocks.record[c].shares ==  -1 ) {
						newStocks.record[c].companyID = save.companyID;
						newStocks.record[c].investorID = save.investorID;
						newStocks.record[c].shares = save.shares;
						return;
					}
				}
			}
		}
		// index points to free previous record pos or free spot

		// check newStocks for same record and remove it
		for (int c = 0; c < newStocks.total; ++c) {
			if( newStocks.record[c].companyID == save.companyID and newStocks.record[c].investorID == save.investorID and newStocks.record[c].shares > 0){
				newStocks.record[c].shares = -1;
			}
		}

		if( !file.write( (char*)&save, sizeof(save) ) )
			FLAG_ERROR = true;

		if( file.is_open() ) file.close();
		return;


	} else {
		Stock search;
		int index = 0;
		while( file.read( (char*)&search, sizeof(search) ) ) {
			if( search.companyID == save.companyID and search.investorID == save.investorID ) {
				file.seekp( index*sizeof(save), file.beg );
				if( !file.write( (char*)&save, sizeof(save) ) ){
					FLAG_ERROR = true;
				}
				if( file.is_open() ) file.close();
				return;
			}
			index++;
		}
		file.clear();
		file.seekp(0,file.end);
		if( !file.write( (char*)&save, sizeof(save) ) ){
			FLAG_ERROR = true;
		}
		if( file.is_open() ) file.close();
		return;
	}
}

bool sellStocks(int iID,int cID,double sum){
	if( iID < 0 or cID < 0 or sum <= 0 ) {
		return false;
	}

	Investor inv = getInvestor(iID);
	Company comp = getCompany(cID);
	Stock st = getStock(iID,cID);
	if ( FLAG_ERROR ) {
		return false;
	}

	if ( st.shares < sum ) {
		return false;
	}

	st.shares -= sum;
	updateStock(st);

	if( FLAG_ERROR ) {
		return false;
	}

	inv.capital += sum;
	return updateInvestor(inv);
}

bool buyStocks(int iID,int cID,double sum){
	if( iID < 0 or cID < 0 or sum <= 0 ) {
		return false;
	}
	Investor inv = getInvestor(iID);
	Company comp = getCompany(cID);
	if ( FLAG_ERROR ) {
		return false;
	}

	if ( inv.capital < sum or comp.price - getCompanySoldShares(comp.id) < sum ) {
		return false;
	}
	Stock s;
	s.companyID = comp.id;
	s.investorID = inv.id;

	Stock check = getStock(s.investorID,s.companyID);
	if( FLAG_ERROR ) {
		FLAG_ERROR = false;
		s.shares = sum;
	} else {
		s.shares = check.shares + sum;
	}

	updateStock(s);

	if( FLAG_ERROR ) {
		return false;
	}

	inv.capital -= sum;

	return updateInvestor(inv);
}

void cacheIfPossible(){
	cache.investors = NULL;
	cache.companies = NULL;
	ifstream file;
	Investor inv;
	Company comp;
	Stock st;
	int fSize;

	cache.freeSpots = new(nothrow) int[500];
	if( !cache.freeSpots )
		return;
	cache.spotCnt = 0;
	cache.spotArraySize = 500;

	newStocks.record = new(nothrow) Stock[100];
	newStocks.total = 100;
	if( !newStocks.record ) {
		delete[] cache.freeSpots;
		return;
	}
	for (int c = 0; c < newStocks.total; ++c) {
		newStocks.record[c].shares = -1;
	}

	file.open(FILE_STOCKS,ios::in | ios::binary);
	if( file ) {
		file.seekg(0,file.end);
		fSize = (int)file.tellg();
		file.seekg(0,file.beg);

		cache.totalStocks = fSize/sizeof(st);

		cache.stockCompany = new(nothrow) int[cache.totalStocks];
		cache.stockInvestor = new(nothrow) int[cache.totalStocks];
		if( cache.stockCompany and cache.stockInvestor ) {
			int c = 0;
			while ( file.read( (char*)&st, sizeof(st) ) ){
				cache.stockInvestor[c] = st.investorID;
				cache.stockCompany[c] = st.companyID;
				++c;
			}
		} else {
			if( !cache.stockInvestor and cache.stockCompany ) {
				delete[] cache.stockCompany;
				cache.stockCompany = NULL;
			}
		}


		if ( file.is_open() )  file.close();
	}

	file.open(FILE_INVESTORS,ios::in | ios::binary);
	if ( file ) {
		file.seekg(0,file.end);
		fSize = (int)file.tellg();
		file.seekg(0,file.beg);

		cache.totalInvestors = fSize/sizeof(inv);

		cache.investors = new(nothrow) int[ cache.totalInvestors ];
		if( cache.investors ){
			int c = 0;
			while ( file.read( (char*)&inv, sizeof(inv) ) )
				cache.investors[c++] = inv.id;
		}

		if( file.is_open() ) file.close();
	}

	file.open(FILE_COMPANIES,ios::in | ios::binary);
	if ( file ) {
		file.seekg(0,file.end);
		fSize = (int)file.tellg();
		file.seekg(0,file.beg);

		cache.totalCompanies = fSize/sizeof(comp);
		cache.companies = new(nothrow) int[ cache.totalCompanies ];
		if( cache.companies ) {
			int c = 0;
			while ( file.read( (char*)&comp, sizeof(comp) ) )
				cache.companies[c++] = comp.id;
		}

		if( file.is_open() ) file.close();
	}
}

double getCompanySoldShares(unsigned companyID){
	ifstream file(FILE_STOCKS,ios::in | ios::binary);
	if( !file ){
		FLAG_ERROR = true;
		return 0;
	}

	Stock s;
	double d = 0.0;
	while( file.read( (char*)&s, sizeof(s) ) ){
		if( s.companyID == companyID )
			d += s.shares;
	}

	if( newStocks.record ) {
		for (int c = 0; c < newStocks.total; ++c) {
			if( newStocks.record[c].companyID == companyID and newStocks.record[c].shares != -1){
				d += newStocks.record[c].shares;
			}
		}
	}

	return d;
}

Stock getStock(unsigned iID,unsigned cID){
	Stock st;

	ifstream file(FILE_STOCKS,ios::in | ios::binary);
	if(!file) {
		FLAG_ERROR = true;
		return st;
	}

	while( file.read( (char*)&st, sizeof(st) ) ) {
		if( st.companyID == cID and st.investorID == iID and st.shares > 0){
			if( file.is_open() ) file.close();
			return st;
		}
	}

	if( newStocks.record ) {
		for (int c = 0; c < newStocks.total; ++c) {
			if( newStocks.record[c].companyID == cID and newStocks.record[c].investorID == iID and newStocks.record[c].shares != -1 )
				return newStocks.record[c];
		}
	}

	FLAG_ERROR = true;
	if( file.is_open() ) file.close();

	return st;
}

Investor getInvestor(unsigned id){
	Investor inv;

	ifstream file(FILE_INVESTORS,ios::in | ios::binary);
	if( !file ){
		FLAG_ERROR = true;
		return inv;
	}

	if ( cache.investors ) {
		int index = -1;
		for (int c = 0; c < cache.totalInvestors; ++c) {
			if (cache.investors[c] == id) {
				index = c;
				break;
			}
		}
		if( index == -1 ){
			if( file.is_open() ) file.close();
			FLAG_ERROR = true;
			return inv;
		}
		file.seekg( index*sizeof(inv), file.beg );
		if( !file.read( (char*)&inv, sizeof(inv) ) ){
			FLAG_ERROR = true;
		}
		if( file.is_open() ) file.close();
		return inv;
	}

	while( file.read( (char*)&inv, sizeof(inv) ) ) {
		if( inv.id == id ) {
			if( file.is_open() ) file.close();
			return inv;
		}
	}
	if( file.is_open() ) file.close();
	FLAG_ERROR = true;
	return inv;

}

Company getCompany(unsigned id){
	Company comp;

	ifstream file(FILE_COMPANIES,ios::in | ios::binary);
	if( !file ){
		FLAG_ERROR = true;
		return comp;
	}

	if ( cache.companies ) {
		int index = -1;
		for (int c = 0; c < cache.totalCompanies; ++c) {
			if (cache.companies[c] == id) {
				index = c;
				break;
			}
		}
		if( index == -1 ){
			if( file.is_open() ) file.close();
			FLAG_ERROR = true;
			return comp;
		}
		file.seekg( index*sizeof(comp), file.beg );
		if( !file.read( (char*)&comp, sizeof(comp) ) ){
			FLAG_ERROR = true;
		}
		if( file.is_open() ) file.close();
		return comp;
	}

	while( file.read( (char*)&comp, sizeof(comp) ) ) {
		if( comp.id == id ) {
			if( file.is_open() ) file.close();
			return comp;
		}
	}
	if( file.is_open() ) file.close();
	FLAG_ERROR = true;
	return comp;
}

bool fileExists(const char *fname){
	fstream file(fname);
	bool isGood = (bool) file;
	if( file.is_open() ) file.close();
	return isGood;
}

void beforeQuit(){
	// if cached and there are empty spaces - re-write stocks file


	if( !cache.freeSpots or !cache.stockInvestor or !cache.stockCompany)
		return; // no cache

	ifstream file( FILE_STOCKS, ios::in | ios::binary );
	ofstream newFile( "stock_temp", ios::out | ios::binary | ios::trunc );
	if( !file or !newFile )
		return;
	Stock mv;

	int index = 0;
	bool write;
	while( file.read( (char*)&mv, sizeof(mv) ) ) {
		write = true;
		for (int c = 0; c < cache.spotCnt; ++c) {
			if( cache.freeSpots[c] == index ) {
				write = false;
				break;
			}
		}
		index++;
		if( !write ) continue;
		newFile.write( (char*)&mv, sizeof(mv) );
	}

	if( newStocks.record ) {
		for (int c = 0; c < newStocks.total; ++c) {
			if( newStocks.record[c].shares > 0 ){
				newFile.write( (char*)&newStocks.record[c], sizeof(newStocks.record[c]) );
			}
		}
	}

	if( file.is_open() ) file.close();
	if( newFile.is_open() ) newFile.close();
	remove( FILE_STOCKS );
	rename( "stock_temp", FILE_STOCKS );

	if( newStocks.record ) delete[] newStocks.record;
	if( cache.stockInvestor ) delete[] cache.stockInvestor;
	if( cache.stockCompany ) delete[] cache.stockCompany;
	if( cache.companies ) delete[] cache.companies;
	if( cache.investors ) delete[] cache.investors;
	if( cache.freeSpots ) delete[] cache.freeSpots;
	cache.stockInvestor = cache.stockCompany = cache.companies = cache.investors = cache.freeSpots = NULL;
	newStocks.record = NULL;
}

bool printInvestor(int iID){
	if( iID < 0 )
		return false;

	Investor inv = getInvestor(iID);
	if( FLAG_ERROR ) {
		return false;
	}

	fstream out(inv.name,ios::out | ios::trunc);

	ifstream file(FILE_STOCKS,ios::in | ios::binary);
	if( !file or !out ) {
		return false;
	}


	out << inv.name << endl;
	out << "                             " << endl; // placeholder

	double shares;
	Stock st;
	Company comp;
	while( file.read( (char*)&st, sizeof(st) ) ) {
		if( st.investorID == inv.id ) {

			if( st.shares <= 0 ) continue;

			comp = getCompany(st.companyID);
			if( FLAG_ERROR ){
				FLAG_ERROR = false;
				continue;
			}
			out << comp.name << setw(30) << fixed << st.shares << endl;
			shares += st.shares;
		}
	}
	if( newStocks.record ) {
		for (int c = 0; c < newStocks.total; ++c) {
			if( newStocks.record[c].investorID == inv.id and newStocks.record[c].shares != -1) {

				comp = getCompany(newStocks.record[c].companyID);
				if( FLAG_ERROR ){
					FLAG_ERROR = false;
					continue;
				}

				out << comp.name << setw(30) << fixed << newStocks.record[c].shares << endl;
				shares += newStocks.record[c].shares;
			}
		}
	}

	out << fixed << setw(60) << ( shares + inv.capital );

	out.close();
	out.open( inv.name, ios::in | ios::out | ios::ate);
	out.seekg(0,out.beg);
	out.seekp(0,out.beg);

	out.seekp( strlen(inv.name) + 2, out.beg ); // move to placeholder

	out << shares;
	out.seekg(0,out.beg);

	return true;

}
