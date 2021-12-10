class Board:
    def __init__(self, values: list[list[int]]):
        self.__values = values

    # Replace every occurance of 'num' with -1
    def draw(self, num: int) -> None:
        height = len(self.__values)
        width = len(self.__values[0])
        for y in range(height):
            for x in range(width):
                if self.__values[y][x] == num:
                    self.__values[y][x] = -1

    # Check if -1's form a horizontal or vertical line
    def hasWon(self) -> bool:
        height = len(self.__values)
        width = len(self.__values[0])

        # Check horizontal lines
        for y in range(height):
            won = True
            for x in range(width):
                if self.__values[y][x] != -1:
                    won = False
                    break
            if won:
                return True

        # Check vertical lines
        for x in range(width):
            won = True
            for y in range(height):
                if self.__values[y][x] != -1:
                    won = False
                    break
            if won:
                return True
        
        return False

    # Calculate the sum of non -1 values
    def getScore(self) -> int:
        sum = 0
        for line in self.__values:
            for value in line:
                if value != -1:
                    sum += value
        return sum

    # Print the board's values
    def print(self):
        for line in self.__values:
            print(line)

def ParseFile(path: str):
    draws = list[int]()
    boards = list[Board]()

    with open(path) as file:
        lines = file.readlines()

        # Draws are comma seperated list on the first line
        draws = [int(x) for x in lines[0].strip().split(',')]

        # Parse and add boards to 'boards'
        values = list[list[int]]()
        for i in range(1, len(lines)):
            line = lines[i].strip()

            # On empty line add the current board and reset 'values'
            # otherwise append the current line to 'values'
            if len(line) == 0: 
                if len(values) > 0:
                    boards.append(Board(values))
                    values = list[list[int]]()
            else:
                values.append([int(x) for x in line.split()])

        # Add the last board if the file did not end with newline
        if len(values) > 0:
            boards.append(Board(values))

    return draws, boards

def part1(path: str) -> int:
    draws, boards = ParseFile(path)

    for num in draws:
        for board in boards:
            board.draw(num)
            if board.hasWon():
                return num * board.getScore()

def part2(path: str) -> int:
    draws, boards = ParseFile(path)

    for num in draws:
        for board in boards:
            board.draw(num)
        if len(boards) == 1 and boards[0].hasWon():
            return num * boards[0].getScore()
        boards = [x for x in boards if not x.hasWon()]

if __name__ == '__main__':
    print(f"PART 1: {part1('input/day4.txt')}")
    print(f"PART 2: {part2('input/day4.txt')}")
