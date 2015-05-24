#!/usr/bin/env python
import sys

if len(sys.argv) != 3:
    print 'Usage: %s file1 file2' % sys.argv[0]
    exit()

a = open(sys.argv[1]).read().strip()
b = open(sys.argv[2]).read().strip()

if a == b:
    print 'Ok'
    exit(0)

print 'WA'
if len(a) != len(b):
    print 'Length of the first file:', len(a)
    print 'Length of the second file:', len(b)
    exit(1)

for i in xrange(len(a)):
    if a[i] != b[i]:
        print '%d char of the first file is "%c", and the corresponding char of the second file is "%c"' % (i, a[i], b[i])
        exit(1)



