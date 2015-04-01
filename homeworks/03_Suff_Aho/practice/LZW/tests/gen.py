#!/usr/bin/env python
import random, string

def f(n):
    s = random.choice(string.lowercase)
    while len(s) < n:
        if random.randint(0, 100) < 20:
            s += random.choice(string.lowercase)
        else:
            l,r = random.randint(0, len(s)), random.randint(0, len(s))
            if l < r:
                s += s[l:r]
            else:
                s += s[r:l]
    return s

testNo = 0
def addTest(n):
    global testNo
    testNo += 1
    with open('%02d.in' % testNo, 'w') as fout:
        fout.write('%s\n' % f(n))

for i in xrange(10):
    addTest(random.randint(2, 20))
for i in xrange(20):
    addTest(random.randint(1000, 10000))
for i in xrange(5):
    addTest(random.randint(2 * 10**5, 3 * 10**5))

