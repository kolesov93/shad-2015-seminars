#!/usr/bin/env python
import random

n = random.randint(900, 1000)
print n

a = [['0'] * n for _ in xrange(n)]
order = range(n)
random.shuffle(order)
for i in xrange(n):
    for j in xrange(n):
        print order[min(i, j, n - i - 1, n - j - 1)] + 1,
    print
