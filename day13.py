from functools import reduce
from math import gcd

with open("day13_input.txt") as f:
    tmp = f.read().split()
    t0 = int(tmp[0])
    bus_lines = enumerate([s if s == 'x' else int(s) for s in tmp[1].split(',')])

# congruence equations
crt = [(-i % b, b) for i, b in bus_lines if b != 'x']


# solve for least solution of
#   x = y0 (mod a0)
#   x = y1 (mod a1)
def solve_least_congruence(t0, t1):
    y0, a0 = t0
    y1, a1 = t1
    x = y0
    while True:
        if x % a1 == y1:
            lcm = (a0 * a1) // gcd(a0, a1)
            return (x, lcm)
        x += a0

print(reduce(solve_least_congruence, crt)[0])