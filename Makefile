GPP=g++

LIBS=-lGL -lSDL -lSDL_image -lGLU -llua5.1

CML=-I $(PWD)/include/cml-1_0_0
LUA=-I /usr/include/lua5.1
INCLUDE=$(CML) $(LUA)

BIN=tview
EXEC=$(PWD)/$(BIN)

DEBUG=-D_DEBUG
#CCFLAGS=-std=c++0x $(DEBUG)
#CCFLAGS=-std=gnu++0x $(DEBUG)
CCFLAGS=$(DEBUG)

SOURCES = $(wildcard src/*.cpp)
HEADERS = $(wildcard src/*.h)

OBJECTS=bin/main.o bin/util.o bin/terrain_vertex.o bin/engine.o bin/view.o bin/light.o bin/window.o bin/args.o bin/terrain.o bin/castle.o bin/primitive.o bin/cylinder.o bin/lua.o
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
	$(EXEC) media/height.png < media/scene
