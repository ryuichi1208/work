#!/usr/bin/python
import subprocess
import sys

args = ['ls', '-l', '-a']

try :
    res = subprocess.call(args)
except :
    print "Error"


