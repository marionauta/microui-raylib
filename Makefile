CFLAGS = -std=c99 -Wall -Wextra
COMMON_SOURCES = src/murl.c vendor/microui.c

.PHONY: all
all: examples/simple examples/font examples/input

examples/simple: examples/simple.c $(COMMON_SOURCES)
	cc $(CFLAGS) -o $@ $^ -I./vendor -I./src `pkg-config --cflags --libs raylib` -lm

examples/font: examples/font.c $(COMMON_SOURCES)
	cc $(CFLAGS) -o $@ $^ -I./vendor -I./src `pkg-config --cflags --libs raylib` -lm

examples/input: examples/input.c $(COMMON_SOURCES)
	cc $(CFLAGS) -o $@ $^ -I./vendor -I./src `pkg-config --cflags --libs raylib` -lm
