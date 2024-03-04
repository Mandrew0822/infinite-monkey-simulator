![alt text](https://github.com/Mandrew0822/monkeys/blob/master/monkey.jpeg)

# Infinite Monkeys Theorem Simulation

This program simulates the Infinite Monkey Theorem, a popular thought experiment in probability theory and statistics.

## Overview

The Infinite Monkey Theorem states that a monkey hitting keys at random on a typewriter keyboard for an infinite amount of time will almost surely type any given text, such as the complete works of William Shakespeare.

In this program, we simulate multiple monkeys typing randomly. Each monkey types a random character every nanosecond. The program prints out the last character each monkey wrote and the time elapsed since the start of the program.

## Features

- Simulates multiple monkeys typing randomly.
- Each monkey types a random character every nanosecond.
- The program prints out the last character each monkey wrote and the time elapsed since the start of the program.

## Usage

The program takes two arguments:

1. The number of monkeys.
2. The time to run the simulation.

The time argument should be a number followed by a unit. The following units are recognized:

- `s` for seconds
- `m` for minutes
- `h` for hours
- `d` for days
- `y` for years

For example, to simulate 10 monkeys for 1 minute, you would run:

monkeys 10 1m


## Building

    git clone https://github.com/Mandrew0822/monkeys.git
    cd monkeys
    ./build


