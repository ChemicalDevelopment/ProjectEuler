from fractions import gcd

# all numbers divisible by these are summed
residues = (3, 5)

# max number to check to (exclusive
max_num = 1000

# returns the result from brute force checking
def brute_force():
	# the end sum
	result = 0
	# loop through every number under max, and manually check
	for i in range(0, max_num):
		# make sure it gets reset 
		add_bool = False
		# manually check all in residues
		for j in residues:
			if i % j == 0:
				# if it passes even one, mark it
				add_bool = True
		# if it is divisible by any residue, add it to the result
		if add_bool:
			result += i
	# return the sum
	return result

# returns the result using accelerated summation techniques
def fast_solution():
	# sums multiples of a up to max (not including)
	def mult(a):
		# use this for max sum (the -1 is because it is exclusive)
		st = (max_num - 1) / a
		# standard summation of a linear sequence
		return (a * (st * (st+1))) / 2
	# s(a)+s(b)-s(lcm(a, b))
	# this part counts the multiples of 3, and 5, but then subtracts off the multiples of 3 and 5 (15), so that they are only counted once
	return mult(residues[0]) + mult(residues[1]) - mult((residues[0] * residues[1]) / gcd(residues[0], residues[1]))

print "Sum of numbers that are multiples of %s up to %s is %s (brute force)" % (" or ".join(map(str, residues)), max_num, brute_force()) 
print "Sum of numbers that are multiples of %s up to %s is %s (fast solution)" % (" or ".join(map(str, residues)), max_num, fast_solution()) 
