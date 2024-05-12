from collections import defaultdict

ans = 0

file = open('input.txt', 'r')
line = file.readline()
while line:
    gn, rounds = line.split(':')
    gid = int(gn[5:])

    rounds = rounds.split(';')

    d = defaultdict(int)

    for round in rounds:
        round = [r.strip().split() for r in round.split(',')]
        for k, color in round:
            d[color] = max(d[color], int(k))

    power = d['red'] * d['green'] * d['blue']
    ans += power

    line = file.readline()

print(ans)
