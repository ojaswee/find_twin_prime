# Finding Twin Prime(s)  

A prime pair or twin prime is a prime number that has a prime gap of two, in other words,
differs from another prime number by two, for example, the twin prime pair(3,5) and (41, 43). We are trying to find these twin primes from 0 to maxValue<br />

----------------------------------------
sequential_program_for_twinPrime.cpp<br /><br />
The most time-consuming code here is <br />
1) finding the prime number and <br />
2) counting/printing twin prime <br />

in parallel code, we want to focus on this part by multithreading <br />

If we are to add parallelization in “sequntial_program_for_twinPrime.cpp”, we will see 2 error from this code <br />
1)	Error in nested for loop <br />
for (int j = 0; j <primeNumbers.size() && (primeNumbers[j] < maxNum / 2) + 1; j++)<br />
Error: termination test in OpenMP ‘for’ statement has improper form<br />
Because of the test case j <primeNumbers.size() && (primeNumbers[j] < maxNum / 2) + 1; <br /> we will have to simplify this condition.<br />
2)	break statement: serialized code allows for break statement but OpenMP we can only have a Structured block. The structured block is a block with one point of entry at the top and one point of exit at the bottom, so break will give us an error.<br />

We can paralyze this sequential code in two ways <br />
1)	each thread gets a prime number to divide the number: inner loop parallelization<br />
2)	each thread gets new number: outer loop parallelization or<br />

-------------------------------------------------------------------------------
parellel_program_for_twinPrime_inner_Loop.cpp<br /><br />
In this code, we divide each new number with different prime numbers.<br />
For example, to see, if 25 is prime, one thread will divide 25 by 2 and another thread 25 by 5. As we can see, <br />
for 25/2 : local= 1 and <br />
for 25/5 : local = 0. <br />
This is the reason we use reduction method. I am using “+” operand to reduce isPrime, which makes initial value of isPrime=0
In the end, add the local variable to isPrime and if isPrime == primeNumber.size() it is a prime number else, not a prime number. 

------------------------------------------------------------------------------- 
parellel_program_for_twinPrime_outerloop.cpp <br /><br />
In this code, I will give each thread a new number to discover if it is a prime number. <br />
For example, one thread is computing to determine if 5 is a prime number and another thread is doing the same computation for 25. <br />In this program 25 can be computed before 5 so I cannot depend on the list of the prime number I have stored in the deque. Hence I am dividing each number from 2 to its square root, and store if it is a prime number. After all the prime numbers are computed, I will sort it first before computing the twin prime. 
