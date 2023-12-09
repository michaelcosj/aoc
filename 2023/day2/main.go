package main

import (
	"fmt"
	"log"
	"os"
	"strconv"
	"strings"
)

func main() {
	testInput := `Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green
Game 2: 1 blue, 2 green; 3 green, 4 blue, 1 red; 1 green, 1 blue
Game 3: 8 green, 6 blue, 20 red; 5 blue, 4 red, 13 green; 5 green, 1 red
Game 4: 1 green, 3 red, 6 blue; 3 green, 6 red; 3 green, 15 blue, 14 red
Game 5: 6 red, 1 blue, 3 green; 2 blue, 1 red, 2 green
    `

	input, err := os.ReadFile("input")
	if err != nil {
		log.Fatal(err)
	}

	_ = testInput
	// fmt.Printf("Part One: %d\n", partOne(string(input)))
	fmt.Printf("Part Two: %d\n", partTwo(string(input)))
}

func partOne(input string) int {
	maxCubeInBag := map[string]int{
		"red":   12,
		"green": 13,
		"blue":  14,
	}

	result := 0
	for _, line := range strings.Split(strings.TrimSpace(input), "\n") {
		tokens := strings.Split(line, ":")
		game, _ := strconv.Atoi(strings.Split(tokens[0], " ")[1])

		possible := true
		sets := strings.Join(tokens[1:], "")

		for _, set := range strings.Split(sets, ";") {
			for _, c := range strings.Split(set, ",") {
				cubes := strings.Split(strings.TrimSpace(c), " ")

				count, _ := strconv.Atoi(cubes[0])
				colour := cubes[1]

				if maxCubeInBag[colour] < count {
					possible = false
				}
			}

			if !possible {
				break
			}
		}
		if possible {
			result += game
		}

	}

	return result
}

func partTwo(input string) int {
	result := 0

	for _, line := range strings.Split(strings.TrimSpace(input), "\n") {
		tokens := strings.Split(line, ":")
		sets := strings.Join(tokens[1:], "")

		power := 0
		maxCount := map[string]int{"red": 0, "blue": 0, "green": 0}
		for _, set := range strings.Split(sets, ";") {
			for _, c := range strings.Split(set, ",") {
				cubes := strings.Split(strings.TrimSpace(c), " ")

				colour := cubes[1]
				count, _ := strconv.Atoi(cubes[0])

				if count > maxCount[colour] {
					maxCount[colour] = count
				}

			}
		}

		power = maxCount["blue"] * maxCount["red"] * maxCount["green"]
		result += power
	}

	return result
}
