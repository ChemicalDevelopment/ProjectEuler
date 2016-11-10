## Problem 357

### Quote

```
Consider the divisors of 30: 1,2,3,5,6,10,15,30.
It can be seen that for every divisor d of 30, d+30/d is prime.

Find the sum of all positive integers n not exceeding 100 000 000
such that for every divisor d of n, d+n/d is prime.
```

### Approach

#### Brute Force

We will sum up integers which this is true, but we can narrow this down.

We only have to check numbers which are in the form:
`4k+2` - Found from empirical evidence (except for the number 1, which we add in seperately)
`p+1 is prime` - One of the divisors of `p` is `p`, so `p+p/p` will be p+1, which must be a prime in order to count it
`p is square free` - If p is not squarefree, then `p=a * b^2`, and if we take `b` as our divisor: `b + p / b = b + a * b = b * (a + 1)` which is obviously not prime, and is in the form of `d+p/d`

To test these, we build arrays which tell us if `p` is prime and squarefree, and whittle them down before we sum them.


### Result 

<details> 
  <summary>Spoiler</summary>
	1739023853137
</details>

The python example on my computer takes just under a minute. A few improvements could be made, such as splicing together the prime and squarefree lists, but this is a happy medium ground.