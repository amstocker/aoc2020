from functools import lru_cache

with open("day10_input.txt") as f:
    data = [0] + sorted([int(x) for x in f.read().split()])


@lru_cache(maxsize=None)
def arrangements(i):
    if i == 0:
        return 1
    total = 0
    j = i - 1
    while (j >= 0) and (data[i] - data[j]) <= 3:
        total += arrangements(j)
        j -= 1
    return total

# Part 2 only
print(arrangements(len(data)-1))