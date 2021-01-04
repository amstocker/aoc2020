from itertools import compress
from day19 import strings, rules

def parse(string):
    suffix, valid = parse_helper([(string, 0)])
    if suffix != "":
        return False
    return valid

def parse_helper(results):
    for string, ruleno in results:
        if string == "":
            return [(string, False)]
        rule = rules[ruleno]
        t = rule[0]
        if type(t) == str:
            if t == string[0]:
                return [(string[1:], True)]
            else:
                return [(string, False)]
        else:
            suffixes = [string] * len(rule)
            i = 0
            while rule:
                m = map(
                    parse_helper,
                    [suffixes[i] for i in range(len(rule)) if i < len(rule[i])],
                    [t[i] for t in rule])
                i += 1

# Part 1
print(sum(parse(s) for s in strings))

# Part 2
rules[8] = [(42,), (42, 8)]
rules[11] = [(42, 31), (42, 11, 31)]
print(sum(parse(s) for s in strings))
