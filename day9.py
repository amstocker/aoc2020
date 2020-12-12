with open("day9_input.txt") as f:
    data = list(map(int, f.read().split()))


# Part 1
n = None
for i in range(25, len(data)):
    found = False
    for j in range(25):
        if (found):
            break
        for k in range(25):
            x = data[i-j-1]
            y = data[i-k-1]
            if (x != y) and data[i] == x + y:
                found = True
                break
    else:
        n = data[i]
        break
print(n)

# Part 2
for i in range(len(data)):
    for j in range(2, len(data) - i):
        if sum(data[i:i + j]) == n:
            print(min(data[i:i + j]) + max(data[i:i + j]))


