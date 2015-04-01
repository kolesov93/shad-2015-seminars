#!/usr/bin/env python
import random, string

limit = 2 * 10**5
qlimit = 5 * (10**4)

loop = random.randint(1, 8)
pattern = ''.join(random.choice('a') for _ in xrange(loop))
text = pattern * random.randint(1, limit / loop)
n = random.randint(len(text), limit)

while len(text) < n:
    text += pattern[len(text) % loop]

errors = random.randint(0, len(text) / 500)
while errors > 0:
    pos = random.randint(0, len(text) - 1)
    text = text[:pos] + 'z' + text[pos+1:]
    errors -= 1

print text
q = random.randint(0, qlimit)
print q
for i in xrange(q):
    print random.randint(0, n - 1), random.randint(0, n)
