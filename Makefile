CFLAGS = -std=c99 -Wall -Wextra
COMMON_SOURCES = src/murl.c vendor/microui.c
EXAMPLES = $(wildcard examples/*.c)

.PHONY: all
all: $(basename $(EXAMPLES))

examples/%: examples/%.c $(COMMON_SOURCES)
	cc $(CFLAGS) -o $@ $^ -I./vendor -I./src `pkg-config --cflags --libs raylib` -lm
