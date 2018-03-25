/*
A prime pair or twin prime is a prime number that has a prime gap of two, in other words,
differs from another prime number by two, for example the twin prime pair (41, 43).
We are tring to find all twin prime numbers between 1 to 2000.
This is a parellel program in OpenMP.
*/

#include <iostream>
#include <omp.h>
#include <ctime>
#include <deque>

using namespace std;

#define NUM_THREADS 8

/*
Only needed if we want to output all twin primes.
In this case I only want count of twin primes.
void printDeque(deque<int>primeNumbers) {
int count = 0;
omp_set_num_threads(NUM_THREADS);
#pragma omp parallel for
for (int i = 0; i < primeNumbers.size() - 1; i++) {
if (primeNumbers.at(i + 1) - primeNumbers.at(i) == 2) {
/*cout << primeNumbers.at(i) << ","
<< primeNumbers.at(i + 1) << endl;*/
/*	count += 1;
}
}
cout << "Pairs of Twin Primes: " << count << endl;
}*/

void findPrime_innerLoop(deque<int>primeNumbers, int maxNum) {
	int count = 0;
	for (int num = 3; num < maxNum; num++) { //max integer we want to check 
		int isPrime = 0;

		//reduction fuction for isPrime is needed
		omp_set_num_threads(NUM_THREADS);
#pragma omp parallel for reduction(+:isPrime)
		for (int j = 0; j <primeNumbers.size(); j++) {
			int local = 0;
			if (num % primeNumbers[j] == 0) { //for composite numbers break the loop
				local = 0;
			}
			else
				local = 1;
			isPrime = local + isPrime;
		}
		if (isPrime == primeNumbers.size()) {
			if ((num - primeNumbers.back()) == 2)
				count += 1;
			primeNumbers.push_back(num);
		}
	}
	cout << "Pairs of Twin Primes: " << count << endl;
	//printDeque(primeNumbers);
}

void main() {
	double duration = 0.00;
	clock_t start;
	deque<int> primeNumbers; //store all the found prime numbers here
	primeNumbers.push_back(2);
	int maxNum = 50;
	start = clock();
	findPrime_innerLoop(primeNumbers, maxNum);
	duration = (clock() - start) / (double)CLOCKS_PER_SEC;

	cout << "\nTime to compute: " << duration << " seconds" << endl; //total seconds passed
	cout << endl;
	system("pause");
}