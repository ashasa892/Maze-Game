CC = g++
SOURCES = Main.cpp App.cpp Map.cpp TextureManager.cpp Network.cpp
OBJECTS = main


LINKER_FLAGS = -lSDL2 -lSDL2_image `pkg-config --cflags --libs SDL2`

all:
	$(CC) $(SOURCES) $(LINKER_FLAGS) -o $(OBJECTS)

server:
	$(CC) server.cpp $(LINKER_FLAGS) -o server

clean:
	rm -f $(OBJECTS)
	rm server