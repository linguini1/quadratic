# quadratic

A simple command line program for solving the quadratic equation. I built this purely to save me a little time when
doing algebra for my engineering homework. The quadratic formula shows up quite often in circuit problems for non-linear
circuits, and it becomes tedious to evaluate the quadratic formula each time.

# Usage

To see usage instructions for this program, please run `quadratic -h`.

Example output:

```console
[user]$ quadratic -- 1 -10 16
1.000000x^2 + -10.000000x + 16.000000
x = 8.000000
x = 2.000000

[user]$ quadratic -v y -- 1 -10 16
1.000000y^2 + 2.000000y + 3.000000
x = -1.000000 + 1.414214i
x = -1.000000 + -1.414214i

```

# Build/Installation

The build recipe is in the Makefile. Running `make all` will create a binary called `quadratic` which you can then run.

Although only tested on Linux, this program should build and run just fine on all other platforms.
