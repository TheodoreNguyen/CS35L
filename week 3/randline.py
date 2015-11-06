#!/usr/bin/python

"""
Output lines selected randomly from a file

Copyright 2005, 2007 Paul Eggert.
Copyright 2010 Darrell Benjamin Carbajal.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

Please see <http://www.gnu.org/licenses/> for a copy of the license.

$Id: randline.py,v 1.4 2010/04/05 20:04:43 eggert Exp $
"""

import random, sys
from optparse import OptionParser

class randline:
    def __init__(self, filename, you, twoyou):
        self.lines = []
        for i in range(len(filename)):
            f = open(filename[i], 'r')
            self.lines = f.readlines() + self.lines
            f.close()
        if self.lines[len(self.lines)-1] != '\n':
            self.lines.append('\n')
        if (you):
            self.lines = list(set(self.lines))
        self.without = twoyou

    def chooseline(self):
    	randompick = random.choice(self.lines)
    	if (self.without):
    		self.lines.remove(randompick)
    	return randompick

def main():
    version_msg = "%prog 2.0"
    usage_msg = """%prog [OPTION]... FILE1 [FILE2 FILE3 FILE4 FILE5...]

Output randomly selected lines from FILE."""

    parser = OptionParser(version=version_msg,
                          usage=usage_msg)
    parser.add_option("-n", "--numlines",
                      action="store", dest="numlines", default=1,
                      help="output NUMLINES lines (default 1)")
    parser.add_option("-u", "--unique",
                      action="store_true", dest="unique", default=False,
                      help="Unique lines only (default False)")
    parser.add_option("-w", "--no-replacement",
                      action="store_true", dest="noreplace", default=False,
                      help="Without replacement (default False)")
    options, args = parser.parse_args(sys.argv[1:])

    try:
        numlines = int(options.numlines)
    except:
        parser.error("invalid NUMLINES: {0}".
                     format(options.numlines))
    if numlines < 0:
        parser.error("negative count: {0}".
                     format(numlines))
    num_inputfiles = len(args)
    try:
        generator = randline(args, options.unique, options.noreplace)
        for index in range(numlines):
            sys.stdout.write(generator.chooseline())
    except IOError as err:
        parser.error("I/O error({0}): {1}".
                     format(errno, strerror))

if __name__ == "__main__":
    main()

