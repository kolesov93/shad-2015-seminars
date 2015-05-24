#!/usr/bin/env python
import random

n = random.randint(1, 10)

edges = []
for i in xrange(n):
    for j in xrange(n):
        edges.append((i+1,j+1))

m = random.randint(0, len(edges))

print n, m
for i in xrange(m):
    edge = random.choice(edges)
    print edge[0], edge[1]
    edges.remove(edge)

