#!/usr/bin/env python
import random
import sys
import os
from math import sqrt

def rnd1(n):
    return random.randint(0, n - 1)

def clamp(x, n):
    if x < 0:
        return 0
    if x >= n:
        return n - 1
    return int(x)

def rnd2(n):
    return clamp(abs(random.normalvariate(float(n) / 2, float(n)**(1./3))), n)

lima = 50000
limb = 100000

n = random.randint(lima, limb)
limc = 1000000 - n

first = [[i] for i in xrange(n)]
random.shuffle(first)


c = random.randint(0, limc)
for _ in xrange(c):
    girl = rnd1(n)
    boy = rnd2(n)
    if girl not in first[boy]:
        first[boy].append(girl)

print n
for girls in first:
    print len(girls), ' '.join(str(x + 1) for x in girls)

