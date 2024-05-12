ans = 0
bads = set()

file = open('input.txt', 'r')

line = file.readline()
while line:
    gn, rounds = line.split(':')
    gid = int(gn[5:])

    ans += gid

    rounds = rounds.split(';')
    for round in rounds:
        round= [r.strip().split() for r in round.split(',')]
        for k, color in round:
            if color == 'red' and int(k) > 12:
                bads.add(gid)
            if color == 'green' and int(k) > 13:
                bads.add(gid)
            if color == 'blue' and int(k) > 14:
                bads.add(gid)

    line = file.readline()

print(ans - sum(bads))
