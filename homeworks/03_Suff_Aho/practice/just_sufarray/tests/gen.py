#!/usr/bin/env python
import random, string

base = 'a'*1000 + 'b'
n = random.randint(10**5 - 100, 10**5)
s = ''.join(random.choice(base) for _ in xrange(n))
sf = sorted([(s[i:], i) for i in xrange(n)])
print s
print ' '.join(str(b) for a,b in sf)

