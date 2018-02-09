#!/usr/bin/env python

# Run over the raw output from
#     xAOD::IOStats::instance().stats().printSmartSlimmingBranchList();
# (If you're copying make sure there are no awkward newlines...)
#
# To add output to your own code, add these includes:
#       #include "xAODCore/tools/ReadStats.h"
#       #include "xAODCore/tools/PerfStats.h"
#       #include "xAODCore/tools/IOStats.h"
# and add the line above to your finalize() function in TheEventLoop

import os

branches = []
with open('branchesused_RAW_r6506.txt') as f:
    lines = f.readlines()

for line in lines:
    bname = line.split(">:")[1].strip()
    if "." in bname:
        base_bname = bname.split(".")[0]
        print base_bname+"."
        for attr in bname.split("."):
            if attr == "-": continue
            if attr == base_bname: continue
            print base_bname+"Dyn."+attr
    else: print bname

