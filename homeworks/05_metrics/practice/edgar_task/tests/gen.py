#!/usr/bin/env python
import random
import sys

N = 100000
M = 200000
C = 1000
K = 10

n = random.randint(1, N)
m = random.randint(n - 1, min(n*5, M))
k = random.randint(0, min(m, K))
print n, m, k

w = range(n)

def fath(x):
    global w
    if w[x] != x:
        w[x] = fath(w[x])
    return w[x]

edges = []
while len(edges) + 1 < n:
    a = random.randint(0, n - 1)
    b = random.randint(0, n - 1)
    if fath(a) != fath(b):
        edges.append((a + 1, b + 1, random.randint(1, C)))
        w[fath(a)] = fath(b)

while len(edges) < m:
    edges.append((random.randint(1, n), random.randint(1, n), random.randint(0, C)))

random.shuffle(edges)

print '\n'.join(' '.join(str(x) for x in _) for _ in edges)


