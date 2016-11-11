//============================================================================
// Name        : PvaPrak1.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tbb/parallel_for.h"
#include "tbb/blocked_range.h"
using namespace std;

class FunktionsObjekt{
public:
	vector<int>& vektorDiesDas;

	FunktionsObjekt(vector<int> &moduloNumber):vektorDiesDas(moduloNumber){}

	void operator()(const tbb::blocked_range<int> range) const {
		for(int i = range.begin(); i < range.end(); i++){
			if(vektorDiesDas[i] > 0){
				vektorDiesDas[i] = 1;
			}
			if(vektorDiesDas[i] == 0){
				vektorDiesDas[i] = 0;
			}
			if(vektorDiesDas[i] < 0){
				vektorDiesDas[i] = -1;
			}
		}
	}
};

int main() {
	time_t t;
	time(&t);
	srand((unsigned int)t);

	vector<int> moduloNumber;
	vector<int> result;
	int n = 20;

	for(int i = 0; i < n; i++){
		int modulo = rand() % 10 ;
		if((rand() % 2) > 0){
			modulo = modulo * (-1);
		}
		cout << modulo << ";";
		moduloNumber.push_back(modulo);
	}
	cout << endl;


	auto lambdaFunction = [&moduloNumber](tbb::blocked_range<int> range){
		for(int i = range.begin(); i < range.end(); i++){
			if(moduloNumber[i] > 0){
				moduloNumber[i] = 1;
			}
			if(moduloNumber[i] == 0){
				moduloNumber[i] = 0;
			}
			if(moduloNumber[i] < 0){
				moduloNumber[i] = -1;
			}
		}
	};

	cout << "Start" << endl;
    double tstart = clock();
	parallel_for(tbb::blocked_range<int>(0,n), lambdaFunction);
    FunktionsObjekt funktionsObjekt(moduloNumber);
    //parallel_for(tbb::blocked_range<int>(0,n), funktionsObjekt);
	cout << "Fertig" << endl;
//	cout << "Dauer: " << (clock() - tstart)/CLOCKS_PER_SEC << std::endl;

	for(int i = 0; i < n; i++){
		cout << moduloNumber[i] << ";";
	}

	return 0;
}
