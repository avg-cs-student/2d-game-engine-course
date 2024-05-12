################################## VARIABLES ###################################
CC           = g++

CFLAGS       = -Wall \
	       -Wfatal-errors \
	       -std=c++17

INCLUDE_PATH = -I"./libs/"

SRC          = src/*.cpp \
               src/game/*.cpp \
	       src/ECS/*.cpp

LFLAGS       = -lSDL2 \
	       -lSDL2_image \
	       -lSDL2_ttf \
	       -lSDL2_mixer \
	       -llua5.3

EXE          = gameengine

#################################### RULES #####################################
build:
	$(CC) $(CFLAGS) $(INCLUDE_PATH) $(SRC) $(LFLAGS) -o $(EXE)

run: build
	./$(EXE)

clean:
	rm -rf $(EXE)
