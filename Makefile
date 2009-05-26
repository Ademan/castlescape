GPP=g++

LIBS=-lGL -lSDL -lSDL_image -lGLU

CML=-I $(PWD)/include/cml-1_0_0
INCLUDE=$(CML)

BIN=tview
EXEC=$(PWD)/$(BIN)

CCFLAGS=-D_DEBUG

HEADERS=src/terrain.h src/terrain_templates.h \
		src/terrain_vertex.h src/math_types.h \
		src/texture.h src/texture_array.h \
		src/mouse.h src/input_handlers.h \
		src/main.h src/util.h

SOURCES = $(wildcard src/*.cpp)
HEADERS = $(wildcard src/*.h)

OBJECTS=bin/main_implementation.o bin/main.o bin/util.o bin/terrain_vertex.o
#OBJECTS=$(wildcard bin/*.o)

#/$(BIN): bin/%.o
# why can't I use a wildcard?
$(BIN): $(OBJECTS)
	$(GPP) $(LIBS) -o $@ $(OBJECTS)
 
bin/%.o: src/%.cpp $(HEADERS)
	$(GPP) $(CCFLAGS) $(INCLUDE) -c -o $@ $<

clean:
	rm $(OBJECTS)
	rm $(BIN)

test: $(BIN)
	$(EXEC) media/sprite.png
