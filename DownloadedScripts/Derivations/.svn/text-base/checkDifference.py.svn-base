#!/usr/bin/env python

# Run over two branch lists, and check if one has anything not contained in the other
# To get branch list from a derivation,
#       asetup 20.1.0.5,here,gcc48 (or whatever's new)
#       checkFile.py dxaod_file.root | gawk '{print $10}' | sort > output.txt

import os

branches_used = []
branches_der = []
branches_all = []
with open('branchesused_r6506.txt') as f:
    branches_used = f.read().splitlines()
with open('derivationbranches_r6506.txt') as f:
    branches_der = f.read().splitlines()
with open ('allbranches_r6506.txt') as f:
    branches_all = f.read().splitlines()

print "Missing branches:"
for branch in branches_used:
    if branch not in branches_der: print branch


print ""
print "Missing branches that exist in original file:"
for branch in branches_used:
    if branch not in branches_der and branch in branches_all: print branch
