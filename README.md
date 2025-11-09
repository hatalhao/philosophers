# Philosophers

Dining Philosophers — a small concurrent C project that implements the classic concurrency problem where philosophers alternately think, eat and sleep while sharing forks (resources). This repository contains a C implementation and a Makefile for building and running the program.

This project was created to practice process/thread synchronization, use of mutexes, and to handle timing and edge cases in concurrent programs.

## Table of Contents

- [Features](#features)
- [Requirements](#requirements)
- [Build](#build)
- [Usage](#usage)
- [Arguments](#arguments)
- [Examples](#examples)
- [Behaviour & Rules](#behaviour--rules)
- [Testing and Debugging Tips](#testing-and-debugging-tips)
- [Project Structure](#project-structure)
- [License & Author](#license--author)

## Features

- Correct synchronization to avoid race conditions.
- Accurate timing for philosopher states (thinking, eating, sleeping).
- Graceful handling of termination conditions.
- Minimal dependencies — POSIX C, pthreads.

## Requirements

- POSIX-compatible OS (Linux, macOS with pthreads).
- gcc (or any C compiler supporting pthreads).
- make

## Build

From the repository root:

```bash
make
```

Common Make targets (provided by the Makefile):

- `make` or `make all` — build the program (default target).
- `make clean` — remove object files.
- `make fclean` — remove object files and binary.
- `make re` — run `fclean` then `all`.

The resulting binary is typically named `philo` (or as specified in the Makefile).

## Usage

Run the program with the following arguments:

```
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

- number_of_philosophers — number of philosophers and forks (integer > 0)
- time_to_die — time in milliseconds after which a philosopher dies if they don't start eating
- time_to_eat — time in milliseconds a philosopher spends eating
- time_to_sleep — time in milliseconds a philosopher spends sleeping
- number_of_times_each_philosopher_must_eat — (optional) if all philosophers eat at least this many times, the simulation stops

Notes:
- All arguments must be positive integers.
- Times are in milliseconds.
- Behavior should be deterministic and properly synchronized so no data races or deadlocks occur.

## Examples

Start a simulation with 5 philosophers:

```bash
./philo 5 800 200 200
```

Start a simulation where each philosopher must eat 7 times:

```bash
./philo 5 800 200 200 7
```

Expected output format (example lines — actual timestamps will vary):

```
0 1 has taken a fork
5 1 is eating
205 1 is sleeping
405 1 is thinking
...
```

Each line usually shows:
- timestamp (ms since start)
- philosopher id
- action (has taken a fork / is eating / is sleeping / is thinking / died)

## Behaviour & Rules

- A philosopher needs two forks to eat.
- Forks are shared between adjacent philosophers.
- A philosopher dies if they don't start eating before time_to_die milliseconds since their last meal or the beginning.
- The simulation ends when a philosopher dies or (if provided) when every philosopher has eaten number_of_times_each_philosopher_must_eat times.
- The program should avoid deadlocks and data races — use mutexes and careful ordering to prevent circular waits.

## Project Structure

- src/ — C source files
- includes/ — headers
- Makefile — build rules
- README.md — this file
