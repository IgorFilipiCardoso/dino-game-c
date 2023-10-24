all: RayCasting MapEditor
	
Packages-Linux:
	if ! dpkg -l | grep ibsdl2-dev -c >>/dev/null; then sudo apt-get install sudo apt-get install libsdl2-dev; fi
	if ! dpkg -l | grep libsdl2-image-dev -c >>/dev/null; then sudo apt-get install sudo apt-get install llibsdl2-image-dev; fi
	if ! dpkg -l | grep libsdl2-mixer-dev -c >>/dev/null; then sudo apt-get install sudo apt-get install libsdl2-mixer-dev; fi
	if ! dpkg -l | grep libsdl2-ttf-dev -c >>/dev/null; then sudo apt-get install sudo apt-get install libsdl2-ttf-dev; fi

RayCasting:

	gcc -o dino-game-linux ./src/main.c ./src/include/*c -I ./SDL2-linux/include -ldl -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
	./RayCasting.exe