# Finding Twin Prime(s)  

A prime pair or twin prime is a prime number that has a prime gap of two, in other words,
differs from another prime number by two, for example, the twin prime pair (41, 43).
We are trying to find all twin prime numbers between 1 to 50.

The most time-consuming code here is   
1) finding the prime number and   
2) counting/printing twin prime  
in parallel code, we want to focus on these part by multithreading and solve following errors.

In parallel code, we will see 2 error from this code  
1)	There is an error in nested for loop   
for (int j = 0; j <primeNumbers.size() && (primeNumbers[j] < maxNum / 2) + 1; j++)  
Error: termination test in OpenMP ‘for’ statement has improper form  
Because of the test case j <primeNumbers.size() && (primeNumbers[j] < maxNum / 2) + 1; we will have to simplify this condition.  
2)	break statement: serialized code allows for break statement but OpenMP we can only have a Structured block. The structured block is a block with one point of entry at the top and one point of exit at the bottom, so break will give us an error.

