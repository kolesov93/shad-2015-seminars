#!/usr/bin/env python
import random, string

n = 10**5
s = 'abacaba'
while len(s) < n: 
    if random.randint(1, 10) < 3:
        l = random.randint(0, min(len(s), n - len(s)))
        start = random.randint(0, len(s) - l)
        s += s[start : start+l ]
    else:
        s += random.choice(string.lowercase)
    
print s
