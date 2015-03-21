#!/usr/bin/env python
import random

lim = 10**6

def calc(a):
    n = len(a)
    b = [0] * n
    for i in xrange(1,n):
        k = b[i - 1]
        while k > 0 and a[k] != a[i]:
            k = b[k - 1]
        if a[k] == a[i]:
            k += 1
        b[i] = k

    return b

def calc_score(a):
    n = len(a)
    pi = calc(a)
    f = [0] * n
    for i in xrange(1, n):
        if pi[i] == 0:
            f[i] = 1
        else:
            f[i] = 1 + f[pi[i] - 1]
    return sum(f)

def gen(fname):
    border = 10**8
    with open(fname, 'w') as f:
        n = lim
        k = 10

        a = [0] * n
        while k > 0:
            a[random.randint(0, n - 1)] = random.randint(0, n)
            k -= 1

        score = calc_score(a)
        while score < border:
            print 'Current score is %d. Need more steps' % score
            ln = random.randint(100, n / 2)
            place = random.randint(1, n - ln)
            c = a[:place] + a[:ln] + a[place+ln:]
            new_score = calc_score(c)
            if new_score > score:
                a = c
                score = new_score
            else:
                print 'Fail'
            print len(a)
        print 'Score is good (%d)' % score

        f.write('%d\n' % len(a))
        f.write(' '.join(str(x) for x in calc(a)))
        f.write('\n')


for i in xrange(1):
    gen('lastbig%02d.in' % i)

