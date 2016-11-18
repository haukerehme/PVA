#include <iostream>
#include <iomanip>
#include <valarray>
#include <cstddef>
#include <ctime>
#include "tbb/parallel_for.h"
#include "tbb/blocked_range.h"
#include "tbb/concurrent_vector.h"

using namespace std;

#define SEQSTANDARD false
#define MYSEQ false
#define MYPARALLEL true

void ausgabeBoolVector(tbb::concurrent_vector<bool> boolVector){
	std::cout << std::endl;
		for(unsigned int i=2; i < boolVector.size();i++)
			if(boolVector[i]==true)
				std::cout << std::setw(5) << i;
		std::cout << std::endl;
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
	//ausgabeausgabeBoolVector(boolVector)
}

void SiebDesEratosthenesParaVersuch2(int n) {
	// --Feld initialisieren.
	tbb::concurrent_vector<bool> boolVector(n,true);
	for(auto i = 2; i*i <= n ; i++){
		if(boolVector[i] == true){
			tbb::parallel_for(tbb::blocked_range<int>(i,(n/i)),
					[&boolVector, &i](tbb::blocked_range<int> range){

				for(int rangeEnd = range.end(), j = range.begin(); j < rangeEnd; j = j + i){
					boolVector[j*i] = false;
				}
			});
		}
	};

	// --Ausgabe der Primzahlen.
	//ausgabeBoolVector(boolVector);
}

void SiebDesEratosthenesSeqVersuch2(int n) {
	// --Feld initialisieren.
	tbb::concurrent_vector<bool> boolVector(n,true);
	//cout << "init abgeschlossen" << endl;
	for(auto i = 2; i*i <= n ; i++){
		//cout << i << endl;
		if(boolVector.at(i) == true){
			for(int j = i; j < n/i; j = j + i){
				//cout << j*i << endl;
				boolVector.at(j*i) = false;
			}
		}
	}

	// --Ausgabe der Primzahlen.
	//ausgabeausgabeBoolVector(boolVector)
}



int main() {
	int anzahlZahlen = (2 << 30) -1;
	time_t t;


	if(SEQSTANDARD){
		t = time(NULL);
		SiebDesEratosthenes(anzahlZahlen);
		cout << time(NULL) - t << endl;
	}

	if(MYSEQ){
		t = time(NULL);
		SiebDesEratosthenesSeqVersuch2(anzahlZahlen);
		cout << time(NULL) - t << endl;
	}

	if(MYPARALLEL){
		t = time(NULL);
		SiebDesEratosthenesParaVersuch2(anzahlZahlen);
		cout << time(NULL) -t << endl;
	}



	return 0;
}
