#!/usr/bin/env python
import random
random.seed(0)

tests = []
for n in xrange(2,27):
    for k in xrange(2, 20):
        if n**k <= 3*10**6:
            if random.randint(0, 10) < 7:
                tests.append((n,k))

tests = sorted(tests, key = lambda x : x[0]**x[1])

no = 4
for test in tests:
    no += 1
    with open('%02d.in' % no, 'w') as f:
        f.write('%d %d\n' % (test[0], test[1]))

