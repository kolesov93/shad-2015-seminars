#!/usr/bin/env python
import random, string

n = random.randint(100, 1000)
print n
a = []

def try_add(pattern, a):
    for c in a:
        if c.startswith(pattern) or pattern.startswith(c):
            return False
    a.append(pattern)
    return True

while len(a) < n:
    if len(a) < 10 or random.randint(0, 100) < 40:
        ln = random.randint(10, 100)
        try_add(''.join(random.choice(string.lowercase) for _ in xrange(ln)), a)
    elif random.randint(0, 100) < 50:
        while True:
            pattern = random.choice(a)
            if len(pattern) / 2 <= 1:
                continue
            ln = random.randint(1, len(pattern) / 2)
            w = pattern[ln:]
            if len(w) > 5:
                try_add(pattern[ln:], a)
                break
    else:
        pattern = random.choice(a)
        l, r = 0, 0
        while l == r:
            l, r = random.randint(1, len(pattern)), random.randint(0, len(pattern))
        if l > r:
            l, r = r, l
        try_add(pattern[l:r], a)

print '\n'.join(a)

m = random.randint(100, 1000)
print m
for i in xrange(m):
    ln = random.randint(100, 1000)
    if random.randint(0, 100) < 10:
        print ''.join(random.choice(string.lowercase) for _  in xrange(l))
    else:
        s = ''.join(random.choice('abcaerfafeqlk') for _ in xrange(ln))
        for itr in xrange(30):
            pattern = random.choice(a)
            if len(pattern) > len(s):
                continue
            pos = random.randint(0, len(s) - len(pattern))
            s = s[:pos] + pattern + s[pos+len(pattern):]
        print s
