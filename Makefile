CFLAGS = -std=c99 -Wall -Wextra

.PHONY: all
all: examples/simple examples/font

examples/simple: examples/simple.c src/murl.c vendor/microui.c
	cc $(CFLAGS) -o $@ $^ -I./vendor -I./src `pkg-config --cflags --libs raylib` -lm

examples/font: examples/font.c src/murl.c vendor/microui.c
	cc $(CFLAGS) -o $@ $^ -I./vendor -I./src `pkg-config --cflags --libs raylib` -lm
