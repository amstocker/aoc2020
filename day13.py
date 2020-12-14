with open("day13_input.txt") as f:
    tmp = f.read().split()
    t0 = int(tmp[0])
    bus_lines = list(enumerate([1 if s == 'x' else int(s) for s in tmp[1].split(',')]))


# print input for WolframAlpha:
#   ChineseRemainder[{0, 34, 920, 4, 6, 12, 349, 20, 9}, {17, 41, 937, 13, 23, 29, 397, 37, 19}]
#   returns...
#   
s = "ChineseRemainder[{}, {}]"
s1 = "{"
s2 = "{"
for i, b in bus_lines:
    if b > 1:
        s1 += "{}, ".format((b - i) % b)
        s2 += "{}, ".format(b)
s1 = s1[:-2] + "}"
s2 = s2[:-2] + "}"
print(s.format(s1, s2))


p = sorted(bus_lines, key=lambda p: -p[1])

# Part 2
t = p[0][1] - p[0][0]
inc = p[0][1]
while True:
    if (t % 1000000 == 0):
        print(t)
    for i, b in bus_lines:
        if (t + i) % b != 0:
            break
    else:
        break
    t += inc
print(t)