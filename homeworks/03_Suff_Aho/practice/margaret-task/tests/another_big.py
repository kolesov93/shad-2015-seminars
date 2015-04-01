#!/usr/bin/env python
import random, string

n = 500
m = 1000
print n
for i in xrange(n):
    print ('b'*i) + ('a'*500)

print m
for i in xrange(m):
    l = random.randint(0, 666)
    print ('b'*l) + ('a'*(1000 - l))
