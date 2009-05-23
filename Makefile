GPP=g++

LIBS=-lGL -lSDL -lSDL_image -lGLU

CML=-I $(PWD)/cml-1_0_0
INCLUDE=$(CML)

BIN=tview
EXEC=$(PWD)/$(BIN)

$(BIN): main.o
	$(GPP) $(LIBS) -o $@ $<
 
main.o: main.cpp terrain.h math_types.h
	$(GPP) $(INCLUDE) -c -o $@ $<

clean:
	rm $(BIN)

test: tview
	$(EXEC) sprite.png
