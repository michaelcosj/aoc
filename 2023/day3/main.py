"""
AOC 2023 DAY 3
------------------------
My solution:
1. I create a function to loop through the input and
    get the coordinates of the numbers and symbols
2. With the coordinates I can solve parts one and two 
    by simply looping through the coordinates and 
    making the necessary calculations based on the 
    conditions given

Time complexity: O(n) 
    Where n is the number of characters in the input
"""

from dataclasses import dataclass

@dataclass
class Number:
    number: int
    pos: tuple
    length: int

@dataclass
class Symbol:
    char: int
    pos: tuple

def get_token_positions(input):
    nums: list[Number] = []
    syms: list[Symbol] = []

    for row, line in enumerate(input.strip().splitlines()):
        number=''
        start=(0, 0)
        length = 0

        prev_char=line.strip()[0]
        for col, char in enumerate(line.strip()):
            if char.isdigit():
                if col == 0 or (not prev_char.isdigit() and col != 0):
                    start = (row, col)
                number += char
                length += 1
                if col == len(line) - 1:
                    nums.append(Number(int(number), start, length))
            else:
                if prev_char.isdigit():
                    nums.append(Number(int(number), start, length))
                    start = (0, 0)
                    length = 0
                    number = ''
                if char != '.' and not char.isspace():
                    syms.append(Symbol(char, (row, col)))

            prev_char = char
    return (nums, syms)

def part_one(input: str):
    result = 0
    nums, syms = get_token_positions(input)

    for num in nums:
        is_adjacent = False
        
        (num_row, num_start) = num.pos
        num_end = num_start + num.length

        for sym in syms:
            (sym_row, sym_col) = sym.pos

            # check for each digit in the number
            for i in range(num_start, num_end):
                # if number is already adjecent go to the next number
                if is_adjacent:
                    break

                # if not adjacent by row
                if not (num_row == sym_row or num_row + 1 == sym_row or num_row - 1 == sym_row):
                    continue

                # if not adjacent by col and diagonal
                if not (i + 1 == sym_col or i - 1 == sym_col or i == sym_col):
                    continue

                result += num.number
                is_adjacent = True

    print(result)


def part_two(input: str):
    result = 0
    nums, syms = get_token_positions(input)

    for sym in syms:
        symbol = sym.char
        if symbol != '*':
            continue

        (sym_row, sym_col) = sym.pos
        adj_nums = [] # adjacent numbers

        for num in nums:
            is_adjacent = False

            if len(adj_nums) > 2:
                break

            (num_row, num_start) = num.pos
            num_end = num_start + num.length

            for i in range(num_start, num_end):
                if is_adjacent:
                    continue

                if not (num_row == sym_row or num_row+1 == sym_row or num_row-1 == sym_row):
                    continue

                if not (i + 1 == sym_col or i - 1 == sym_col or i == sym_col):
                    continue

                is_adjacent = True

            if is_adjacent: adj_nums.append(num.number)

        if len(adj_nums) == 2:
            ratio = adj_nums[0] * adj_nums[1]
            result += ratio

    print(result)

def main():
    testInput = """
        467..114..
        ...*......
        ..35..633.
        ......#...
        617*......
        .....+.58.
        ..592.....
        ......755.
        ...$.*....
        .664.598..
    """

    input = ''
    with open('input', 'r') as inputFile:
        input = inputFile.read()

    part_one(input)
    part_two(input)

if __name__ == "__main__":
    main()
