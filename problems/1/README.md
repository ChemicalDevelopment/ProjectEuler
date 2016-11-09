## Problem 1

### Quote

```
If we list all the natural numbers below 10 that are multiples of 3 or 5, we get 3, 5, 6 and 9. The sum of these multiples is 23.

Find the sum of all the multiples of 3 or 5 below 1000.
```

### Approach

#### Brute Force

We want to find the sum of all `k` such that `k = 0 mod 3 or k = 0 mod 5`

This simple solution is the `brute_force` solution.

#### Fast Solution
We will use the following equality:

`sum(k) for k = 0...n = n(n+1)/2`

and the fact that:

`sum(a*k) for k = 0...n = a*n(n+1)/2`

### Result 

<details> 
  <summary>Spoiler</summary>
   233168 
</details>

They are both extremely fast for such a small example, and either one is fine for this example. 

The brute force search was a little bit faster to code, and is arguably more human error resistant to code.