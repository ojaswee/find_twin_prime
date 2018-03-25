/*
A prime pair or twin prime is a prime number that has a prime gap of two, in other words,
differs from another prime number by two, for example the twin prime pair (41, 43).
We are tring to find all twin prime numbers between 1 to 50.
This is a parellel program in OpenMP.
*/

#include <iostream>
#include <omp.h>
#include <ctime>
#include <deque>
#include <algorithm>

using namespace std;

#define NUM_THREADS 8

/*
Only needed if we want to output all twin primes.
In this case I only want count of twin primes.*/
void printDeque(deque<int>primeNumbers) {
	int count = 0;
	//sorting prime numbers before finding twin prime
	sort(primeNumbers.begin(), primeNumbers.end());
	omp_set_num_threads(NUM_THREADS);
#pragma omp parallel for
	for (int i = 0; i < primeNumbers.size()-1; i++) {
		if (primeNumbers.at(i + 1) - primeNumbers.at(i) == 2) {
		//cout <<primeNumbers.at(i) << "," << primeNumbers.at(i + 1) << endl;
			count += 1;
		}
	}
	cout //<< "size "<<primeNumbers.size()
		<<"\nPairs of Twin Primes: " << count << endl;
}

void findPrime_outerLoop(deque<int>primeNumbers, int maxNum) {
	//int count = 0;
	omp_set_num_threads(NUM_THREADS);
#pragma omp parallel for //reduction(+:isPrime)
	for (int num = 5; num < maxNum; num+=2) { //max integer we want to check 
		bool isPrime = false;
		for (int j = 2; j <=sqrt(num); j++) {
			if ((num % j) == 0) { //for composite numbers break the loop
				isPrime = false;
				j = sqrt(num)+1;
			}
			else
				isPrime = true;
		}
		if (isPrime) {
			//cout << num<<" ";
			primeNumbers.push_back(num);
		}
	}
	printDeque(primeNumbers);
}

void main() {
	double duration = 0.00;
	clock_t start;
	deque<int> primeNumbers; //store all the found prime numbers here
	primeNumbers.push_back(2);
	primeNumbers.push_back(3);
	int maxNum = 50;
	start = clock();
	findPrime_outerLoop(primeNumbers, maxNum);
	duration = (clock() - start) / (double)CLOCKS_PER_SEC;

	cout << "\nTime to compute: " << duration << " seconds" << endl; //total seconds passed
	cout << endl;
	system("pause");
}