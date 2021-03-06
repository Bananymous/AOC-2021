def part1(path: str) -> int:
    x = y = 0

    with open(path, 'r') as file:
        for line in file:
            command = line.split()[0]
            amount  = int(line.split()[1])

            if command == "forward":
                x += amount
            elif command == "down":
                y += amount
            elif command == "up":
                y -= amount

    return x * y

def part2(path: str) -> int:
    x = y = 0
    aim = 0

    with open(path, 'r') as file:
        for line in file:
            command = line.split()[0]
            amount = int(line.split()[1])

            if command == "forward":
                x += amount
                y += aim * amount
            elif command == "down":
                aim += amount
            elif command == "up":
                aim -= amount

    return x * y

if __name__ == '__main__':
    print(f"PART 1: {part1('input/day2.txt')}")
    print(f"PART 2: {part2('input/day2.txt')}")