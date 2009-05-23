GPP=g++

LIBS=-lGL -lSDL -lSDL_image -lGLU

CML=-I $(PWD)/include/cml-1_0_0
INCLUDE=$(CML)

BIN=tview
EXEC=$(PWD)/$(BIN)

CCFLAGS=-D_DEBUG

HEADERS=src/terrain.h src/math_types.h \
		src/texture.h src/texture_array.h \
		src/mouse.h src/input_handlers.h \
		src/main.h

SOURCES=src/main.cpp src/main_implementation.cpp

OBJECTS=bin/main_implementation.o bin/main.o

#/$(BIN): bin/%.o
# why can't I use a wildcard?
$(BIN): bin/main_implementation.o bin/main.o
	$(GPP) $(LIBS) -o $@ $(OBJECTS)
 
bin/%.o: src/%.cpp $(HEADERS)
	$(GPP) $(CCFLAGS) $(INCLUDE) -c -o $@ $<

clean:
	rm $(BIN)

test: $(BIN)
	$(EXEC) media/sprite.png
