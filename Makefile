
run: build
	./build/monkey-chess-engine

build: src/*
	gcc -o monkey-chess-engine src/* -g `sdl2-config --cflags --libs` -lSDL2 -lSDL2_image
	mv monkey-chess-engine build/monkey-chess-engine

build_win32: src/*
	x86_64-w64-mingw32-gcc -mwin32 -o monkey-chess-engine_win32 src/* `sdl2-config --cflags --libs` -lSDL2 -lSDL2_image
	mov monkey-chess-engine_win32 build/monkey-chess-engine_win32

open:
	nvim src/*
