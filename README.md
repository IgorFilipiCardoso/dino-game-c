# Prototipo de testes do jogo do Dino em C e SDL2

Repositorio para testes e aprendizado, este código não foi feito para ser o melhor, apenas para eu aprender como usar a ferramenta SDL2 com C.

Foi usado:

- C
- [SDL2](https://github.com/libsdl-org/SDL)
- [SDL_image](https://github.com/libsdl-org/SDL_image)
- [SDL_mixer](https://github.com/libsdl-org/SDL_mixer)
- [SDL_ttf](https://github.com/libsdl-org/SDL_ttf)

-> Como baixar SDL2 e suas bibliotecas?

  Para Windowns:
  - Baixe essas versoes: SDL2-devel-2.28.4-mingw.zip / SDL2_image-devel-2.6.3-mingw.zip / SDL2_mixer-devel-2.6.3-mingw.zip
  - Apos baixar todos, extraia, e mescle a pasta 'lib' e 'include' do SDL2_image e SDL2_mixer na pasta do SDL2.
  - Pegue as pastas 'lib' e 'include' e mova para uma pasta SDL2.
  - Entre nas pastas 'bin' e pegue as DLLs, mova as DLLs para a pasta raiz do seu projeto.


  Para Linux:

  - sudo apt-get install libsdl2-dev
  - sudo apt-get install libsdl2-image-dev
  - sudo apt-get install libsdl2-mixer-dev
  - sudo apt-get install libsdl2-ttf-dev


-> Como compilar?

Apos ter feito o download do SDL2, SDL_image, SDL_mixer e do SDL_ttf:

Para windowns:

-Digite o comando no terminal:

-  gcc -std=c99 -o dino-game-win.exe ./src/main.c ./src/lib/*c -I ./SDL2/include -L ./SDL2/lib/ -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -mwindows

Para Linux (Ubunto):

-Digite o comando no terminal:

- gcc -o dino-game-linux ./src/main.c ./src/include/*c -I ./SDL2-linux/include -ldl -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

A IDE utilizada foi o VsCode no Windowns.
