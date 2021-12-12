def ParseFile(path: str) -> list[list[int]]:
    result = list[list[int]]()
    with open(path, 'r') as file:
        for line in file:
            result.append([int(x) for x in line.strip()])
    return result

def part1(path: str) -> int:
    octos = ParseFile(path)
    w = len(octos)
    h = len(octos[0])
    
    # list of offsets for every adjacent coordinate
    adjacents = [(-1, -1), (-1, 0), (-1, 1), (0, -1), (0, 1), (1, -1), (1, 0), (1, 1)]

    count = 0
    for _ in range(100):
        # increase every energy level by 1
        for i in range(h):
            for j in range(w):
                octos[i][j] += 1

        # store flashed octopus coordinates to avoid multiple flashes
        # of the same octpus
        flashed = set()

        while True:
            start_len = len(flashed)

            # flash every octopus with energy level > 9
            for i in range(h):
                for j in range(w):
                    if octos[i][j] > 9 and not (i, j) in flashed:
                        for k, l in adjacents:
                            if 0 <= i + l < h and 0 <= j + k < w:
                                octos[i + l][j + k] += 1
                        flashed.add((i, j))

            # if no more flashes happened, break out
            if len(flashed) == start_len:
                break

        count += len(flashed)

        # reset every flashed octopus to 0
        for i, j in flashed:
            octos[i][j] = 0

    return count


# Basically the exactly same as part1() except return the current step
# once every cell flashes simultaneously
def part2(path: str) -> int:
    octos = ParseFile(path)
    w = len(octos)
    h = len(octos[0])
    
    # list of offsets for every adjacent coordinate
    adjacents = [(-1, -1), (-1, 0), (-1, 1), (0, -1), (0, 1), (1, -1), (1, 0), (1, 1)]

    step = 0
    while True:
        step += 1

        # increase every energy level by 1
        for i in range(h):
            for j in range(w):
                octos[i][j] += 1

        # store flashed octopus coordinates to avoid multiple flashes
        # of the same octpus
        flashed = set()

        while True:
            start_len = len(flashed)

            # flash every octopus with energy level > 9
            for i in range(h):
                for j in range(w):
                    if octos[i][j] > 9 and not (i, j) in flashed:
                        for k, l in adjacents:
                            if 0 <= i + l < h and 0 <= j + k < w:
                                octos[i + l][j + k] += 1
                        flashed.add((i, j))

            # if no more flashes happened, break out
            if len(flashed) == start_len:
                break
        
        # if the number of flashes is same as grid size, return current step
        if len(flashed) == w * h:
            return step

        # reset every flashed octopus to 0
        for i, j in flashed:
            octos[i][j] = 0


if __name__ == "__main__":
    print(f"PART 1: {part1('input/day11.txt')}")
    print(f"PART 2: {part2('input/day11.txt')}")