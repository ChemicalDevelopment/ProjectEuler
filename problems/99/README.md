## Problem 99

### Quote

```
Comparing two numbers written in index form like 211 and 37 is not difficult, as any calculator would confirm that 211 = 2048 < 37 = 2187.

However, confirming that 632382518061 > 519432525806 would be much more difficult, as both numbers contain over three million digits.

Using base_exp.txt (right click and 'Save Link/Target As...'), a 22K text file containing one thousand lines with a base/exponent pair on each line, determine which line number has the greatest numerical value.

NOTE: The first two lines in the file represent the numbers in the example given above.
```

### Approach

We loop through the csv, parse the base, exp pairs, then compute the log of base**exp (by using exp * log(base))

This creates the same ordinal effect which we can compare

### Result 

<details> 
  <summary>Spoiler</summary>
   709
</details>

Works extremely fast
