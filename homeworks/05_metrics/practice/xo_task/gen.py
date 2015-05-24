#!/usr/bin/env python
import random
import sys
import os

lima = 1
limb = 10
limc = 0
limp = 5

def gen():
    n = random.randint(lima, limb)
    m = random.randint(lima, limb)
    mp = [['?'] * m for i in xrange(n)]
    c = random.randint(0, limc)
    for i in xrange(c):
        mp[random.randint(0, n - 1)][random.randint(0, m - 1)] = '*'
    return mp

def gen2():
    n = random.randint(lima, limb)
    m = random.randint(lima, limb)
    os.system('echo "%d %d" | ./gen > buffer.in' % (n, m))
    mp = []
    with open('buffer.in') as f:
        n, m = map(int, f.readline().split())
        for line in f:
            mp.append(line.strip())
    return mp


while True:
    mp = gen2()
    with open('buffer.in', 'w') as f:
        n = len(mp)
        m = len(mp[0])
        f.write('%d %d\n' % (n, m))
        f.write('\n'.join(''.join(x) for x in mp))
        f.write('\n')

    os.system('./sol < buffer.in > buffer.out')

    with open('buffer.out') as f:
        ans = f.readline().strip()
        if 'Poor' in ans:
            print >> sys.stderr, 'Bad iteration'
            continue
        print n, m
        mp = []
        for line in f:
            mp.append(line.strip())

        for row in mp:
            nrow = []
            for c in row:
                if c == '*':
                    nrow.append('*')
                else:
                    if random.randint(0, 100) < limp:
                        nrow.append(c)
                    else:
                        nrow.append('?')
            print ''.join(nrow)
        break

