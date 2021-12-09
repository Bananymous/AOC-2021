def parseFile(path: str) -> list[int]:
    res = []
    with open(path) as file:
        for line in file:
            res.append(int(line))
    return res

def part1(path: str) -> int:
    nums = parseFile(path)
    ans = 0
    for i in range(1, len(nums)):
        if nums[i - 1] < nums[i]:
            ans += 1
    return ans

def part2(path: str) -> int:
    nums = parseFile(path)
    ans = 0
    for i in range(3, len(nums)):
        if nums[i - 3] < nums[i]:
            ans += 1
    return ans

if __name__ == "__main__":
    print(f"PART 1: {part1('input/day1.txt')}")
    print(f"PART 2: {part2('input/day1.txt')}")