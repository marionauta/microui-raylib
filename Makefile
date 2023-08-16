CFLAGS = -std=c99 -Wall -Wextra

examples/simple: examples/simple.c src/murl.c vendor/microui.c
	cc $(CFLAGS) -o $@ $^ -I./vendor -I./src `pkg-config --cflags --libs raylib` -lm
