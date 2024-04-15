CC = gcc
OUT = quadratic

# Compilation warnings
WARNINGS += -Wall -Wextra -Wshadow -Wundef -Wformat=2 -Wtrampolines -Wfloat-equal
WARNINGS += -Wbad-function-cast -Wstrict-prototypes -Wpacked
WARNINGS += -Wno-aggressive-loop-optimizations -Wmissing-prototypes -Winit-self
WARNINGS += -Wmissing-declarations -Wmissing-format-attribute -Wunreachable-code
WARNINGS += -Wshift-overflow=2 -Wduplicated-cond -Wpointer-arith -Wwrite-strings
WARNINGS += -Wnested-externs -Wcast-align -Wredundant-decls
WARNINGS += -Werror=implicit-function-declaration -Wlogical-not-parentheses
WARNINGS += -Wlogical-op -Wold-style-definition -Wcast-qual -Wdouble-promotion
WARNINGS += -Wunsuffixed-float-constants -Wmissing-include-dirs -Wnormalized
WARNINGS += -Wdisabled-optimization -Wsuggest-attribute=const

# Compilation flags
CFLAGS = -O3 -lm

# Source files
SRCDIR = .
SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(patsubst %.c,%.o,$(SRCS))

%.o: %.c
	$(CC) $(CFLAGS) $(WARNINGS) -o $@ -c $<

all: $(OBJS)
	$(CC) $(CFLAGS) $^ -o $(OUT)

clean:
	@rm $(OBJS)
