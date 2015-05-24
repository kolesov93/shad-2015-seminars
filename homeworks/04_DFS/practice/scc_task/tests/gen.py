#!/usr/bin/env python
import random

elimit = 150000

def doit(fname, alimit, blimit):
    n = random.randint(alimit, blimit)
    with open(fname, 'w') as f:
        edges = []
        m2 = n**2
        flag = True
        if m2 < 1000:
            for i in xrange(n):
                for j in xrange(n):
                    edges.append((i+1,j+1))
            m = random.randint(0, len(edges))
        else:
            flag = False
            m = random.randint(0, min(n*n, elimit))
            done = set()

        f.write('%d %d\n' % (n, m))
        for i in xrange(m):
            if flag:
                edge = random.choice(edges)
                edges.remove(edge)
            else:
                while True:
                    edge = (random.randint(1, n), random.randint(1, n))
                    if edge not in done:
                        break
                done.add(edge)
            f.write('%d %d\n' % edge)

for testNo in xrange(3, 50):
    doit('%02d.in' % testNo, 1, 20)
for testNo in xrange(50, 90):
    doit('%02d.in' % testNo, 1000, 100000)
for testNo in xrange(90, 100):
    doit('%02d.in' % testNo, 90000, 100000)


