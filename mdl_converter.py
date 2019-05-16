import sys

if __name__ == '__main__':
    if len(sys.argv) <= 2:
        print('no')
    f = open(sys.argv[1], 'r')
    t = open(sys.argv[2], 'w')

    while f.readline():
        l = f.readline()
        c = l.split()
        if len(c) == 0:
            continue
        if c[0] == 'v':
            t.write(' '.join(c))
            t.write('\n')
        if c[0] == 'f':
            r = c[0] + ' ' + c[1].split('/')[0] + ' ' + c[2].split('/')[0] + ' ' + c[3].split('/')[0]
            t.write(r)
            t.write('\n')

