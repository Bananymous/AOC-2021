from os import O_TEXT


def ParseFile(path: str) -> list[str]:
    res = []
    with open(path) as file:
        for line in file:
            res.append(line.strip())
    return res

def part1(path: str) -> int:
    nums = ParseFile(path)
    bits = len(nums[0])

    gamma = ""
    epsilon = ""

    for i in range(bits):
        count = 0
        for num in nums:
            if num[i] == '1':
                count += 1
        if count > len(nums) / 2:
            gamma += '1'
            epsilon += '0'
        else:
            gamma += '0'
            epsilon += '1'
    
    return int(gamma, 2) * int(epsilon, 2)

def part2(path: str) -> int:
    nums = ParseFile(path)
    bits = len(nums[0])

    oxygen = nums
    co2 = nums

    for i in range(bits):
        if len(oxygen) <= 1:
            break

        # Calculate set bits in ith position
        count = 0
        for num in oxygen:
            if num[i] == '1':
                count += 1

        # Erase the least common bit (0 or 1)
        if count >= len(oxygen) / 2:
            oxygen = [x for x in oxygen if x[i] == '1']
        else:
            oxygen = [x for x in oxygen if x[i] == '0']

    for i in range(bits):
        if len(co2) <= 1:
            break

        # Calculate set bits in ith position
        count = 0
        for num in co2:
            if num[i] == '1':
                count += 1
                
        # Erase the most common bit (0 or 1)
        if count < len(co2) / 2:
            co2 = [x for x in co2 if x[i] == '1']
        else:
            co2 = [x for x in co2 if x[i] == '0']

    return int(oxygen[0], 2) * int(co2[0], 2)


if __name__ == '__main__':
    print(f"PART 1: {part1('input/day3.txt')}")
    print(f"PART 2: {part2('input/day3.txt')}")