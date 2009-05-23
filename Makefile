GPP=g++

LIBS=-lGL -lSDL -lSDL_image -lGLU

CML=-I $(PWD)/include/cml-1_0_0
INCLUDE=$(CML)

BIN=tview
EXEC=$(PWD)/$(BIN)

CCFLAGS=-D_DEBUG

HEADERS=src/terrain.h src/math_types.h src/texture.h
SOURCES=src/main.cpp

$(BIN): bin/main.o
	$(GPP) $(LIBS) -o $@ $<
 
#bin/%.o: %.cpp
bin/main.o: src/main.cpp $(HEADERS)
	$(GPP) $(CCFLAGS) $(INCLUDE) -c -o $@ $<

clean:
	rm $(BIN)

test: $(BIN)
	$(EXEC) media/sprite.png


test: $(BIN)
	$(EXEC) media/sprite.png

