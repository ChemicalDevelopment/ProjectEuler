#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int max = 100000000;

int *primes;

int m32 = (1<<5)-1;

#define set_bit(set, n, val) (set[n>>5] = _set_bit(set, n, val))
#define get_bit(set, n) (_get_bit(set, n))

int _set_bit(int *bs, int id, int val) {
	return bs[id>>5] ^ (-val ^ bs[id>>5]) & (1 << (id & m32));
}

int _get_bit(int *bs, int id) {
	return (bs[id>>5] >> (id & m32)) & 1;
}


int all_div_prime(int n) {
	if (!(get_bit(primes, n+1))) return 0;
	int i;
	for (i = 2; i * i <= max; ++i) {
		if (n % i == 0) {
			if (!get_bit(primes, i + n / i)) {
				return 0;
			}
		}
	}
	return 1;
}

void calc_sets() {
	primes = (int *)malloc(sizeof(int)*(max/32+1));
	int i, j;
	int prime_const = (int)((((long long)(2)<<(34))-1)/3);
	for (i = 0; i <= max/32; ++i) {
		primes[i] = prime_const;
	}
	set_bit(primes, 0, 0);
	set_bit(primes, 1, 0);
	set_bit(primes, 2, 1);
	for (i = 3; i * i <= max; i += 2) {
		if (get_bit(primes, i)) {
			for (j = 3 * i; j <= max; j += 2 * i) {
				set_bit(primes, j, 0);
			}
		}
	}
}


int main(int argc, char *argv[]) {
	long long i, total = 1;
	clock_t start, end;
	start = clock();
	calc_sets();
	for (i = 2; i <= max; i += 4) {
		if (all_div_prime(i)) {
			total += i;
		}
	}
	end = clock();
	printf("%lld, took %lf\n", total, ((double)(end-start))/CLOCKS_PER_SEC);
}


