#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// golden ratio, phi^2=phi+1
double phi;

//Returns nth fibonacci number
int f(int n) {
	return round((pow(phi, n) - pow(1 - phi, n)) / sqrt(5.d));
}

// returns sum of multiples of a or b up to max (exclusive)
int brute_force(int max) {
	//Init f(n) and f(n+1), and sum
	int a = 1, b = 2, sum = 0;
	//Keep looping until one is less than max
	while (a < max && b < max) {
		// if they are even, add them to the sum
		if (a % 2 == 0) sum += a;
		if (b % 2 == 0) sum += b;
		// assign new fibo numbers
		a = a + b;
		b = a + b;
	}
	// return
	return sum;
}

//returns sum of multiples of a or b up to max (exclusive) using summing multiples
int elegant_solution(int max) {
	//init sum, loop, and nth fibo number
	int n = 3, sum = 0, fn = f(n);
	//keep going until it goes over max value
	while (fn < max) {
		// we know that f(3n) are the only even fibonacci numbers, so keep incrementing
		sum += fn;
		fn = f(n += 3);
	}
	//return the accumulated value
	return sum;
}

int main(int argc, char *argv[]) {
	//initialize phi to calculate fibo numbers using binet's formula
	phi = (1.d+sqrt(5.d))/(2.);
	//initialize default max
	int max = 4000000;
	//If the user enters more, replace defaults
	if (argc > 1) max = strtol(argv[1], NULL, 10);

	//Print out info for both approaches
	printf("Sum of even fibonacci numbers up to %d is %d (brute force)\n", max, brute_force(max));
	printf("Sum of even fibonacci numbers up to %d is %d (elegant solution)\n", max, elegant_solution(max));
	return 0;
}