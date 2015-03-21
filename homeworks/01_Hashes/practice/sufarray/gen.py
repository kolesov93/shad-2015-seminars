#!/usr/bin/env python
import random, string

n = int(raw_input())
print ''.join(random.choice(string.lowercase) for i in xrange(n))
