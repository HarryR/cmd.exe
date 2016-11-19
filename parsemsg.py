#!/usr/bin/env python
import sys
import re
import json

MSG_RX = re.compile(r'^MessageId=([^ ]+) SymbolicName=([^\n]+)\n' +
                    r'Language=([^\n]+)\n(.*?)\n\.\n', re.M | re.S)


def main():
    if len(sys.argv) < 2:
        print "Usage: parsemsg.py <file>"
        return 1
    entries = []
    for filename in sys.argv[1:]:
        data = open(filename).read()
        data = data.replace("\r\n", "\n")
        entries += MSG_RX.findall(data)
    print '#include "cmd.h"'
    print 'const cmdmsg_t g_cmdmsg[] = {'
    N = 0
    for entry in entries:
        msgstr = json.dumps(entry[3])
        if N > 0:
            print ',',
        N += 1
        print '{0x%08xL, "%s", %s}' % (int(entry[0]), entry[1], msgstr)
    print ', {0xFFFFFFFF, "_END_", "_END_"}'
    print '};'


if __name__ == "__main__":
    sys.exit(main())
