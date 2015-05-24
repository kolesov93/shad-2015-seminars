#!/usr/bin/env python
import random

def f(n, out):
    a = [['0'] * n for _ in xrange(n)]

    order = range(n)
    random.shuffle(order)
    for c in order:
        l = random.randint(0, n - 1)
        r = random.randint(l, n - 1)
        d = random.randint(0, n - 1)
        u = random.randint(d, n - 1)
        for x in xrange(l, r + 1):
            for y in xrange(d, u + 1):
                a[x][y] = str(c + 1)

    out.write('%d\n' % n)
    for row in a:
        out.write('%s\n' % ' '.join(row))
    out.close()

for i in xrange(3, 40):
    f(random.randint(2, 20), open('%02d.in' % i, 'w'))
for i in xrange(40, 80):
    f(1000 - random.randint(0, 20), open('%02d.in' % i, 'w'))
