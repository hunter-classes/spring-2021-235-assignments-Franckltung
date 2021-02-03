#include <iostream>
/*
6! = 6*5!
  5! = 5*4!
  4! = 4*6
  3! = 3*2
  2! = 2*1
  1! = 1 *1
  0! = 1
  fact(n) = {  1 if n = 0
               n * (n-1)! otherwise
Things to look for in a recursive solution:
1. Base case <-- when you just know the answer without recurring
2. reduction <-- the recursive call that will eventually get to the base case
Things to consider
1. Try small examples by hand
2. look for self similarity - smaller simpler problems 
*/

int fact(int n){
	if (n == 0){
		return 1;
	} 
	else {
		return n * fact(n-1);
	}
}

/*
 *
 1 1 2 3 5 8 13 21 34
 the next fib number is the sum of the previous two fib numbers
*/

int fib(int n){
	if (n <2){
		return 1;
	} 
	else {
		return fib(n-1) + fib(n-2);
	}
}

int fib_iter(int n) {
	// Zeroth Fibonacci number doesn't exist
	if (n < 1) {
		std::cout << "Error; \"" << n << "\" is out of range.\n";
		return 0;
	}
	// Store the previous number and add it to the current one to create the new one
	int previous = 0;
	int current = 1;
	for (int i = 1; i < n; i++) {
		int newPrevious = current;
		current += previous;
		previous = newPrevious;
	}
	return current;
}
int main()
{
	int i;
	for (i = 0; i < 10 ; i++){
		std::cout << i << "! = " << fact(i) << "\n";
    }

	for (i=0; i < 10 ; i++){
		std::cout << fib_iter(i) << ", ";
    }
    std::cout << "\n";
	
	return 0;
}
