#include <iostream>
#include <iomanip>
#include <valarray>
#include <cstddef>
#include <ctime>
#include "tbb/parallel_for.h"
#include "tbb/blocked_range.h"
#include "tbb/concurrent_vector.h"

using namespace std;

void SiebDesEratosthenesParaVersuch1(int n) {
	// --Feld initialisieren.
	tbb::concurrent_vector<bool> boolVector(n,true);
//	valarray<bool> a(true,n-1);

	// --Durchlaufe alle Zahlen bis sqrt(n).
	//int i=2;

	/*auto lambdaEratosthenes = [&boolVector, &i, &n ](tbb::blocked_range<int> range){
		//cout << "i:" << i << "->" << range.begin() << "-" << range.end() << "; ";
		int j = range.begin();
		while(j % i != 0 && j < range.end()){
			j++;
		}
		while(j < range.end()){
	//		cout << "--> !" << j << "!   "  ;
			boolVector[j] = false;
			j = j + i;
		}
	};*/


	//lambdaEratosthenes(tbb::blocked_range<int>(2,sqrt(n)));
	for(auto i = 2; i*i <= n ; i++){
		if(boolVector[i] == true){
			tbb::parallel_for(tbb::blocked_range<int>(i+i,n), [&boolVector, &i, &n ](tbb::blocked_range<int> range){
				//cout << "i:" << i << "->" << range.begin() << "-" << range.end() << "; ";
				int j = range.begin();
				while(j % i != 0 && j < range.end()){
					j++;

				}
				while(j < range.end()){
			//		cout << "--> !" << j << "!   "  ;
					boolVector[j] = false;
					j = j + i;
				}
			});
		//	cout << endl;
			//tbb::parallel_for(tbb::blocked_range<int>(i,n), lambdaEratosthenes);
		}
	};

	//cout << endl;

	/*for(auto i = 2; i*i<=n;i++){
		if(boolVector[i-2]==true){
			// --Vielfache der Primzahlen sieben.
			for(int j = 2*i; j <= n; j += i)
				boolVector[j-2]=false;
		}
	}*/

	/*while(i*i<=n) {
		if(boolVector[i-2]==true)
		// --Vielfache der Primzahlen sieben.
		for(int j = 2*i; j <= n; j += i)
			boolVector[j-2]=false;
		i++;

	}*/

	// --Ausgabe der Primzahlen.
	/*std::cout << std::endl;
	for(unsigned int i=2; i < boolVector.size();i++)
		if(boolVector[i]==true)
			std::cout << std::setw(5) << i;
		std::cout << std::endl;*/
}

void SiebDesEratosthenes(int n) {
	// --Feld initialisieren.
	tbb::concurrent_vector<bool> boolVector(n,true);

	// --Durchlaufe alle Zahlen bis sqrt(n).
	int i=2;

	while(i*i<=n) {
		if(boolVector[i-2]==true)
		// --Vielfache der Primzahlen sieben.
		for(int j = 2*i; j <= n; j += i)
			boolVector[j-2]=false;
		i++;
	}

	// --Ausgabe der Primzahlen.
	/*std::cout << std::endl;
	for(unsigned int i=2; i < boolVector.size();i++)
		if(boolVector[i-2]==true)
			std::cout << std::setw(5) << i;
		std::cout << std::endl;*/
}

void SiebDesEratosthenesParaVersuch2(int n) {
	// --Feld initialisieren.
	tbb::concurrent_vector<bool> boolVector(n,true);

	/*std::cout << std::endl;
		for(unsigned int i=2; i < boolVector.size();i++)
			std::cout << std::setw(5) << i;
			std::cout <<  std::endl;*/

	for(auto i = 2; i*i <= n ; i++){
		if(boolVector[i] == true){
			tbb::parallel_for(tbb::blocked_range<int>(i,(n/i)),
					[&boolVector, &i](tbb::blocked_range<int> range){
				//cout << "i:" << i << "->" << range.begin()*i << "-" << range.end()*i << "; ";
				for(int j = range.begin(); j <= range.end(); j = j + i){
					//cout << "--> !" << j << "!   "  ;
					boolVector[j*i] = false;
				}
			});
			//cout << endl;
		}
	};

	//cout << endl;

	// --Ausgabe der Primzahlen.
	/*std::cout << std::endl;
	for(unsigned int i=2; i < boolVector.size();i++)
		if(boolVector[i]==true)
			std::cout << std::setw(5) << i;
		std::cout << std::endl;*/
}

void SiebDesEratosthenesSeqVersuch2(int n) {
	// --Feld initialisieren.
	tbb::concurrent_vector<bool> boolVector(n,true);

	for(auto i = 2; i*i <= n ; i++){
		if(boolVector[i] == true){
			[&boolVector, &i,&n](tbb::blocked_range<int> range){
				for(int j = i; j <= n/i; j = j + i){
					boolVector[j*i] = false;
				}
			};
		}
	};

	//cout << endl;

	// --Ausgabe der Primzahlen.
	/*std::cout << std::endl;
	for(unsigned int i=2; i < boolVector.size();i++)
		if(boolVector[i]==true)
			std::cout << std::setw(5) << i;
		std::cout << std::endl;*/
}

int main() {
	int anzahlZahlen = 1000000000;
	clock_t start;
	int laufzeit;

	/*start = clock();
	SiebDesEratosthenes(anzahlZahlen);
	laufzeit = (clock() - start);
	cout << laufzeit<<" <-- Laufzeit sequentiell"<<endl;*/

	start = clock();
	SiebDesEratosthenesSeqVersuch2(anzahlZahlen);
	laufzeit = (clock() - start);
	cout << laufzeit<< " <-- Laufzeit SeqVersuch2" << endl;

	start = clock();
	SiebDesEratosthenesParaVersuch2(anzahlZahlen);
	laufzeit = (clock() - start);
	cout << laufzeit<< " <-- Laufzeit ParaVersuch2" << endl;

	/*start = clock();
	SiebDesEratosthenesParaVersuch1(anzahlZahlen);
	laufzeit = (clock() - start);
	cout << laufzeit << " <-- Zeit parallel Versuch1" << endl;*/


	return 0;
}
