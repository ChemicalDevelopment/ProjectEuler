# maximum value of fibonacci number
max_num = 4000000

# returns the result from brute force checking
def brute_force():
	su = 0
	a = 1
	b = 2
	while a < max_num and b < max_num:
		if a % 2 == 0: su += a
		if b % 2 == 0: su += b
		a = a + b
		b = a + b
	return su

# returns the result using accelerated techniques
"""
We know that f(n) = (p**n-(-p)**n)/sqrt(5) (binet's formula)

and if f(3) = 2, and f(3n)=0 mod 2, we just take the values of f_(3n) and sum those

A little bit more elegant than the other one

"""
def elegant_solution():
	# golden ratio
	p = (1+5**.5)/2
	# returns nth fibonacci number
	def f(n):
		return int((p**n - (1-p)**n)/(5**.5))
	# total sum
	su = 0
	# what index
	n = 3
	# nth fibo number
	fn = f(n)
	# keep going until it exceeds max
	while fn < max_num:
		# add to sum
		su += fn
		# increase n
		n += 3
		# set fn to the nth fibo number
		fn = f(n)
	#return sum
	return su

# print info
print "Sum of even fibonacci numbers up to %s is %s (brute force)" % (max_num, brute_force()) 
print "Sum of even fibonacci numbers up to %s is %s (elegant solution)" % (max_num, fast_solution()) 
