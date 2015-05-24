#!/usr/bin/env python
import random

n = 10**6
m = 10**5
k = 30

for _ in xrange(m):
    was = [False, False]
    for __ in xrange(k):
        was[random.randint(0,1)] = True
    if was[0] == False or was[1] == False:
        print 'Fail'
        exit(1)
exit(0)

