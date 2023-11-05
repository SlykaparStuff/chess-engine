
run: build
	./build/monkey-chess-engine

build: src/*
	gcc -o monkey-chess-engine src/* `sdl2-config --cflags --libs` -lSDL2 -lSDL2_image
	mv monkey-chess-engine build/monkey-chess-engine

build_win32: src/main.c src/main.c src/game.h src/game.c
	i686-w64-mingw32-gcc -o monkey-chess-engine src/main.c src/game.c `sdl2-config --cflags --libs` -lSDL2 -lSDL2_image

open:
	nvim src/*
