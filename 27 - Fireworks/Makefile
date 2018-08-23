output=.\\dist\\game

SFML=..\SFML
SFMLLIBS = -L$(SFML)\lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
SFML_INCLUDE= -I$(SFML)\include

all: compiled
	echo Build success, running aplication... && $(output)
compiled: main.o cell.o
	g++ main.o cell.o -o  $(output) $(SFMLLIBS)

main.o : main.cpp Cell.cpp Cell.hpp
	g++ -c main.cpp $(SFML_INCLUDE)

cell.o : Cell.cpp Cell.hpp
	g++ -c Cell.cpp $(SFML_INCLUDE) -o cell.o