/*
AOC 2023 DAY 1
------------------------
My solution:
1.  I parse the input and use two cursors from the front and
    back of each line to check if a number exists.
2. When a number if found the loop terminates and the number is added up to
    the results.
3. In part two I use a table to check if the current string of letters
    from the front, and from the back are one of the strings that represents
    the digit

Time complexity: O(n)
    Where n is the number of characters in the input
*/

#include "stdio.h"
#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int INPUT_HEIGHT = 1000;
int INPUT_WIDTH = 50;
int BUF_LEN = 256;

char *get_input() {
  char *input = malloc((sizeof(char) * (INPUT_HEIGHT * INPUT_WIDTH)));
  char buf[BUF_LEN];

  FILE *f = fopen("./input", "r");
  if (f == NULL) {
    printf("error reading file");
    exit(EXIT_FAILURE);
  }

  while (fgets(buf, BUF_LEN, f)) {
    strncat(input, buf, BUF_LEN);
  }
  input[strlen(input)] = '\0';

  return input;
}

int part_one(char *input) {
  int result = 0;
  char *line = strtok(input, "\n");

  while (line != NULL) {
    int len = strlen(line);
    int first = 0, last = 0;
    int front = 0, back = len;

    while (first == 0 || last == 0 && (front <= len && back >= 0)) {
      char c = line[front];
      if (isdigit(c) && first == 0) {
        first += (int)(c - '0') * 10;
      }

      c = line[back];
      if (isdigit(c) && last == 0) {
        last += (int)(c - '0');
      }

      front += 1, back -= 1;
    }
    line = strtok(NULL, "\n");
    result += first + last;
  }
  return result;
}

int part_two(char *input) {
  int result = 0;
  char *line = strtok(input, "\n");

  while (line != NULL) {
    int len = strlen(line);

    int first = 0, last = 0;
    int front = 0, back = len;

    while (first == 0 || last == 0 && (front <= len && back >= 0)) {
      char c = line[front];
      if (isdigit(c) && first == 0) {
        first = (int)(c - '0') * 10;
      }

      c = line[back];
      if (isdigit(c) && last == 0) {
        last = (int)(c - '0');
      }

      const char *table[] = {"one", "two",   "three", "four", "five",
                             "six", "seven", "eight", "nine"};

      if (len - front >= 3 && first == 0) {
        char buf[5];
        strncpy(buf, line + front, 5);
        for (size_t i = 0; i < sizeof(table) / sizeof(table[0]); i++) {
          if (strncmp(buf, table[i], strlen(table[i])) == 0) {
            first = (i + 1) * 10;
            break;
          }
        }
      }

      if (len - back >= 3 && last == 0) {
        char buf[5];
        strncpy(buf, line + back, 5);
        for (size_t i = 0; i < sizeof(table) / sizeof(table[0]); i++) {
          if (strncmp(buf, table[i], strlen(table[i])) == 0) {
            last = (i + 1);
            break;
          }
        }
      }

      front += 1, back -= 1;
    }
    result += first + last;
    line = strtok(NULL, "\n");
  }
  return result;
}

int main(int argc, char *argv[]) {
  char part_one_test_input[] = "1abc2\n"
                               "pqr3stu8vwx\n"
                               "a1b2c3d4e5f\n"
                               "treb7uchet\n";

  char part_two_test_input[] = "two1nine\n"
                               "eightwothree\n"
                               "abcone2threexyz\n"
                               "xtwone3four\n"
                               "4nineeightseven2\n"
                               "zoneight234\n"
                               "7pqrstsixteen\n";
  char *input = get_input();

  // int part_one_result = part_one(input);

  int part_two_result = part_two(input);
  printf("Result: %d\n", part_two_result);

  free(input);

  return EXIT_SUCCESS;
}
