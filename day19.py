with open("day19_input.txt") as f:
    tmp = f.read()
    tmp = tmp.split('\n\n')

strings = tmp[1].strip().split('\n')
rules = {}
terminal_rules = {}
max_ruleno = 0
for line in tmp[0].split('\n'):
    ruleno = int(line[:line.index(':')])
    max_ruleno = max(max_ruleno, ruleno)
    if '"' in line:
        i = line.index('"')
        c = line[i + 1:i + 2]
        rules[ruleno] = c
        terminal_rules[ruleno] = c
        continue
    subrules = []
    for t in map(lambda s: s.strip().split(), line[line.index(':') + 1:].split('|')):
        subrules.append(tuple(map(int, t)))
    rules[ruleno] = subrules



# generates lexicographically ordered tuples of the form
#   (i_0, i_1, ..., i_n)
# where
#   a = i_0 < i_1 < ... < i_n = b
def partitions(a, b, n, t = ()):
    if t == ():
        yield from partitions(a + 1, b, n, t = (a,))
    elif n == 1:
        yield t + (b,)
    else:
        for i in range(a, b):
            yield from partitions(i + 1, b, n - 1, t = t + (i,))

# yields generators of partitions of s into n substrings
def string_partitions(s, n):
    for t in partitions(0, len(s), n):
        yield (s[t[i]:t[i+1]] for i in range(n))


# caches results of `process`
_valid = set()
_invalid = set()
def reset_cached():
    global _valid
    global _invalid
    _valid = set(terminal_rules.items())
    _invalid = set()

def cache_valid_and_invalid(f):
    def decorated(*args):
        if args in _valid:
            return True
        if args in _invalid:
            return False
        if f(*args):
            _valid.add(args)
            return True
        _invalid.add(args)
        return False
    return decorated

@cache_valid_and_invalid
def process(ruleno, string):
    if type(ruleno) == str:
        return False
    return any(
        all(process(r, s) for r, s in zip(subrules, partition)) \
            for subrules in rules[ruleno] \
            for partition in string_partitions(string, len(subrules)) 
    )


# Part 1
reset_cached()
count = 0
for s in strings:
    if process(0, s):
        count += 1
print(count)

# Part 2
rules[8] = [(42,), (42, 8)]
rules[11] = [(42, 31), (42, 11, 31)]
reset_cached()
count = 0
for s in strings:
    if process(0, s):
        count += 1
print(count)
