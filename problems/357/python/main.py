import time

# our number to max 
max = 100000000

# this is the maximum number that will be computed by d+p/d
max_val = max+1

# arrays used to test primality. We only need half for the prime array because we know 2 * k is not prime except for k = 1
primes = [True] * (max_val / 2)
squarefree = [True] * (max_val)

# returns True if n is prime, False otherwise
def isprime(n):
	if n == 2: return True
	if n % 2 == 0: return False
	return primes[n>>1]

# returns True of n =/= a^2 * b for any integers a and b
def issquarefree(n):
	return squarefree[n]

# sieves for primes and square free integers
def set_sieve():
	# the prime set is represented in that primes[i] tells whether 2*i+1 is prime, so p[3] is 7 being prime, in order to save space
	primes[0] = False
	i = 3
	while i < max_val:
		if primes[i>>1]:
			j = 3 * i
			while j < max_val:
				primes[j>>1] = False
				j += 2 * i
		i += 2
	i = 2
	while i * i < max_val:
		for j in range(i * i, max_val, i * i):
			squarefree[j] = False
		i += 1

# returns true if the general rule for summing (that d + p/d is prime for all divisors) is true
def all_div_prime(n):
	# escape early if conditions are not met
	if not (isprime(n+1) and issquarefree(n)):
		return False
	i = 1
	# maximum factor is sqrt(n)
	lim = int(n**.5)+1
	# loop through
	while i <= lim:
		if n % i == 0:
			if not isprime(i + n / i):
				return False
		i+=1
	return True

# returns the total sum
def search():
	# all are in the form 4k+2 except for 1, which we manually dd in
	total_sum = 1
	for i in range(2, max+1, 4):
		# if it works, add it to the sum
		if all_div_prime(i):
			total_sum += i
	return total_sum

# time sieving and searching
start = time.time()
set_sieve()
# give an indication to where wer are
print "Done sieving"

print "Total: %d (brute)" % (search())
end = time.time()
print "Took %f seconds" % (end - start)

