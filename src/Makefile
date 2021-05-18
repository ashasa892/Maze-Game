CC = g++
SOURCES = Main.cpp App.cpp Map.cpp TextureManager.cpp 	
OBJECTS = main


LINKER_FLAGS = -lSDL2 -lSDL2_image

all:
	$(CC) $(SOURCES) $(LINKER_FLAGS) -o $(OBJECTS)

clean:
	rm -f $(OBJECTS)