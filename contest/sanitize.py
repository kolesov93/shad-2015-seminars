#!/usr/bin/env python
import string

fname = 'mockinbird_raw.txt'
with open(fname) as f:
    content = f.read()

allowed = string.letters + ' ' + "()':,.!?'" + '"'

result = []
for c in content:
    nw = ' '
    if c in allowed:
        nw = c
    if len(result) == 0 or (nw in string.letters or result[-1] != nw):
        result.append(nw)
print ''.join(result)



