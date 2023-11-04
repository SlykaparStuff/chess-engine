
run: build
	./build/chess

build: src/main.c src/game.h src/game.c
	gcc -o chess src/main.c src/game.c `sdl2-config --cflags --libs` -lSDL2 -lSDL2_image
	mv chess build/chess

build_win32: src/main.c src/main.c src/game.h src/game.c
	i686-w64-mingw32-gcc -o chess src/main.c src/game.c `sdl2-config --cflags --libs` -lSDL2 -lSDL2_image

