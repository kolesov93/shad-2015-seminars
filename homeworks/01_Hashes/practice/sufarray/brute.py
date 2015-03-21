#!/usr/bin/env python

s = raw_input().strip()
print ' '.join(str(len(s) - len(x) + 1) for x in sorted(s[i:] for i in range(len(s))))


