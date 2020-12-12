from functools import lru_cache

with open("day10_input.txt") as f:
    data = sorted(list(map(int, f.read().split())) + [0])


# Part 2 (only)

@lru_cache(maxsize=None)
def arrangements(i):
    total = 0
    if i == 0:
        return 1
    j = i - 1
    while (j >= 0) and (data[i] - data[j]) <= 3:
        total += arrangements(j)
        j -= 1
    return total

print(arrangements(len(data)-1))