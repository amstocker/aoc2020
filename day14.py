with open("day14_input.txt") as f:
    data = f.read().split('\n')


# Part 1
memory = {}
for line in data:
    if line[0:4] == "mask":
        mask = line[7:]
        mask0 = int(mask.replace('X', '0'), 2)
        mask1 = int(mask.replace('X', '1'), 2)
    if line[0:3] == "mem":
        loc = int(line[4:line.find(']')])
        num = int(line[line.find(']') + 4:])
        memory[loc] = (num | mask0) & mask1
print(sum(memory.values()))


# Part 2
def build_addrs(loc, mask):
    locs = [i for i, c in enumerate(mask) if c == 'X']
    temp = format(loc | int(mask.replace('X', '0'), 2), '036b')
    addrs = []
    for i in range(2**len(locs)):
        new_mask = list(temp)
        for j in range(len(locs)):
            new_mask[locs[j]] = str((i & (1 << j)) >> j)
        addrs.append(int(''.join(new_mask), 2))
    return addrs

memory = {}
for line in data:
    if line[0:4] == "mask":
        mask = line[7:]
    if line[0:3] == "mem":
        loc = int(line[4:line.find(']')])
        num = int(line[line.find(']') + 4:])
        for addr in build_addrs(loc, mask):
            memory[addr] = num
print(sum(memory.values()))