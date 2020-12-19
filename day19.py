with open("day19_input.txt") as f:
    tmp = f.read()
    tmp = tmp.split('\n\n')

rules = {}
for line in tmp[0].split('\n'):
    ruleno = int(line[:line.index(':')])
    if '"' in line:
        i = line.index('"')
        rules[ruleno] = str(line[i + 1:i + 2])
        continue
    tmp2 = map(lambda s: s.strip().split(), line[line.index(':') + 1:].split('|'))
    subrules = []
    for t in tmp2:
        subrules.append(tuple(map(int, t)))
    rules[ruleno] = subrules


valid_substrings = set([])
invalid_substrings = set([])
def process(s, ruleno):
    if (s, ruleno) in valid_substrings:
        return True
    if (s, ruleno) in invalid_substrings:
        return False
    rule = rules[ruleno]
    if type(rule) == str:
        if s == rule:
            valid_substrings.add((s, ruleno))
            return True
        invalid_substrings.add((s, ruleno))
        return False
    maybes = []
    for t in rule:
        if len(t) == 1:
            maybes.append(process(s, t[0]))
        elif len(t) == 2:
            for i in range(1, len(s)):
                maybes.append(process(s[:i], t[0]) and process(s[i:], t[1]))
    if any(maybes):
        valid_substrings.add((s, ruleno))
        return True
    invalid_substrings.add((s, ruleno))
    return False


# Part 1
count = 0
for s in tmp[1].split('\n'):
    print(s)
    if process(s, 0):
        count += 1
print(count)