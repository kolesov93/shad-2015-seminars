#!/usr/bin/env python
import random, string

text = ['a','b'] * 100000
text[100000] = 'q'

print ''.join(text)
q = 100000
print q
n = len(text)
for i in xrange(q):
    while True:
        l = random.randint(0, n - 1)
        k = random.randint(1000, n)
        if l + k + k <= n:
            break
    print l, k
