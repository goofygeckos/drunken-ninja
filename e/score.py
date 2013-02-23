import sys

file, A, B = sys.argv[1:]
A = int(A)
B = int(B)

program = open(file).read()

S = len(program.split('\n')) + program.count("PUSH")

print 20 + 80 * (A - S) / float(A - B)
