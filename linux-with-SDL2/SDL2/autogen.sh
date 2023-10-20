#!/bin/sh

set -e

"${ACLOCAL:-aclocal}" -I acinclude
"${AUTOMAKE:-automake}" --foreign --include-deps --add-missing --copy
"${AUTOCONF:-autoconf}"

echo "Now you are ready to run ./configure"
gcc -o dino-game-linux ./src/main.c ./src/include/*c -I ./SDL2/include -L ./SDL2/lib/ -lSDL2 -lSDL2_image -lSDL2_mixer

