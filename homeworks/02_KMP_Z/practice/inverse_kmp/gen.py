#!/usr/bin/env python
import random

n = random.randint(1, 10)
print n
m = random.randint(1, n + n)
a = [random.randint(0, m) for i in xrange(n)]

for i in xrange(n):
    res = i
    while res > 0:
        if a[:res] == a[i - res+1:i+1]:
            break
        res -= 1
    print res,
print
