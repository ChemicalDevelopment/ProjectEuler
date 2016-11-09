#include <stdio.h>
#include <stdlib.h>

// Sums multiples up of k up to _max (exclusive)
int sum_mult(int k, int _max) {
	int max = _max - 1;
	return k * (max/k)*(max/k+1) / 2;
}

// returns gcd of a and b
int gcd(a, b) {
	int c = 0;
	// uses euclidean algorithm
	while (b) {
		c = b;
		b = a % b;
		a = c;
	}
	return a;
}
// returns lcm of a and b, the least common multiple of both a and b
int lcm(a, b) {
	return a * b / gcd(a, b);
}

// returns sum of multiples of a or b up to max (exclusive)
int brute_force(int max, int a, int b) {
	//init sum and loop variables
	int i, sum = 0;
	for (i = 0; i < max; ++i) {
		// if i is divisible by a or b, add to the sum
		if (i % a == 0 || i % b == 0) {
			sum += i;
		}
	}
	//return sum
	return sum;
}

//returns sum of multiples of a or b up to max (exclusive) using summing multiples
int fast_solution(int max, int a, int b) {
	//s(a)+s(b)-s(lcm(a, b))
	//This gives multiples of a and b, but subtracts numbers divisible by both, so it isn't counted twice
	return sum_mult(a, max) + sum_mult(b, max) - sum_mult(lcm(a, b), max);
}

int main(int argc, char *argv[]) {
	//initialize defaults
	int max = 1000, a = 3, b = 5, ci = 1;
	//If the user enters more, replace defaults
	if (argc > ci) max = strtol(argv[ci++], NULL, 10);
	if (argc > ci) a = strtol(argv[ci++], NULL, 10);
	if (argc > ci) b = strtol(argv[ci++], NULL, 10);

	//Print out info for both approaches
	printf("Sum of numbers that are multiples of %d or %d up to %d is %d (brute force)\n", a, b, max, brute_force(max, a, b));
	printf("Sum of numbers that are multiples of %d or %d up to %d is %d (fast solution)\n", a, b, max, fast_solution(max, a, b));
	return 0;
}