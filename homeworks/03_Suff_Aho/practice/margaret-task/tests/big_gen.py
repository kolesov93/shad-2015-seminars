#!/usr/bin/env python
import random, string

n = 1000
m = 1000
print n
s = 'a'*n
for i in xrange(n):
    print s[:i] + 'z'

print m
for i in xrange(m):
    print s
