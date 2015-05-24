#!/usr/bin/env python
import random

n = random.randint(900, 1000)
a = [['0'] * n for _ in xrange(n)]

order = range(n)
random.shuffle(order)
for c in order:
    l = random.randint(0, n - 1)
    r = random.randint(0, n - 1)
    d = random.randint(0, n - 1)
    u = random.randint(0, n - 1)
    if l > r:
        l, r = r, l
    if d > u:
        d, u = u, d
    for x in xrange(l, r + 1):
        for y in xrange(d, u + 1):
            a[x][y] = str(c + 1)

print n
for row in a:
    print ' '.join(row)

