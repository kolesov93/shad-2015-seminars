#!/usr/bin/env python
import random

lim = 10**6

def gen(fname):
    with open(fname, 'w') as f:
        n = lim - random.randint(0, 1000)

        a = [0]
        while len(a) < n:
            if random.randint(0, 10) >= 2:
                a += a[:random.randint(1, len(a))]
            else:
                a.append(random.randint(0, len(a)))
        if len(a) > lim:
            a = a[:lim]

        n = len(a)
        f.write('%d\n' % n)
        b = [0] * n
        print n
        for i in xrange(1,n):
            k = b[i - 1]
            while k > 0 and a[k] != a[i]:
                k = b[k - 1]
            if a[k] == a[i]:
                k += 1
            b[i] = k
        f.write('%s\n' % ' '.join(str(x) for x in b))

for i in xrange(15):
    gen('superbig%02d.in' % i)

